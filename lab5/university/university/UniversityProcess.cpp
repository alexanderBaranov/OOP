#include "stdafx.h"
#include "UniversityProcess.h"
#include <fstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/format.hpp>

using namespace std;

static const string kName = "���";
static const string kGender = "���";
static const string kAge = "�������";
static const string kGrowth = "����";
static const string kWeight = "���";
static const string kUniversity = "�����������";
static const string kNumberOfYearsStudy = "���������";

CUniversityProcess::CUniversityProcess(
	std::string listOfUniversity, 
	std::string listOfStudents)
	:m_universitiesFile(listOfUniversity),
	m_studentsFile(listOfStudents)
{
	Load(listOfUniversity, listOfStudents);
	m_updated = false;
}

CUniversityProcess::~CUniversityProcess()
{
}

void CUniversityProcess::Load(
	const std::string listOfUniversity, 
	const std::string listOfStudents)
{
	string contentListOfUniversity = ReadInputFile(listOfUniversity);
	vector<string> values;
	ParseWordsSeparatedByCommas(contentListOfUniversity, values);

	for (const string& val : values)
	{
		const auto univer = FindUniversity(val);
		if (!FindUniversity(val))
		{
			m_universities.push_back(make_shared<CUniversity>(CUniversity(val)));
		}
	}

	values.clear();

	string contentListOfStudents = ReadInputFile(listOfStudents);
	ParseBaseData(contentListOfStudents, values);

	for (size_t i = 0; i < values.size(); i++)
	{
		string name, gender, age, growth, weight, university, numberOfYearsStudy;

		if (values[i] == kName)
		{
			name = values[++i];
		}

		if (values[++i] == kGender)
		{
			gender = values[++i];
		}

		if (values[++i] == kAge)
		{
			age = values[++i];
		}

		if (values[++i] == kGrowth)
		{
			growth = values[++i];
		}

		if (values[++i] == kWeight)
		{
			weight = values[++i];
		}

		if (values[++i] == kUniversity)
		{
			university = values[++i];
		}

		if (values[++i] == kNumberOfYearsStudy)
		{
			numberOfYearsStudy = values[++i];
		}

		const auto univer = FindUniversity(university);
		if (univer)
		{
			m_students.push_back(make_shared<CStudent>(name, 
													gender, 
													stod(growth), 
													stod(weight), 
													stoi(age), 
													univer, 
													stoi(numberOfYearsStudy)));
		}
	}
}

void CUniversityProcess::Save()
{
	if (!m_updated)
	{
		return;
	}

	ofstream outUniversitiesFile(m_universitiesFile);
	outUniversitiesFile.exceptions(ios::badbit);

	for (size_t i = 0; i < m_universities.size(); i++)
	{
		string str(m_universities[i]->GetName());
		outUniversitiesFile << "\"" << str << "\"" << endl;
	}

	outUniversitiesFile.close();

	ofstream outStudentsFile(m_studentsFile);
	outStudentsFile.exceptions(ios::badbit);

	for (const auto& students : m_students)
	{
		string str(kName + "[" + students->Name() + "], ");
		str.append(kGender + "[" + students->Gender() + "], ");
		str.append(kAge + "[" + to_string(students->Age()) + "], ");
		str.append(kGrowth + "[" + to_string(students->Growth()) + "], ");
		str.append(kWeight + "[" + to_string(students->Weight()) + "], ");
		str.append(kUniversity + "[" + students->UniversityName() + "], ");
		str.append(kNumberOfYearsStudy + "[" + to_string(students->NumberOfYearsStudy()) + "];");

		outStudentsFile << str << endl;
	}

	outStudentsFile.close();
}

const universites CUniversityProcess::GetListUniversites() const
{
	return m_universities;
}

const students CUniversityProcess::GetListStudents() const
{
	return m_students;
}

bool CUniversityProcess::ReplaceUniversity(const std::string oldName, const std::string newName)
{
	auto univer = FindUniversity(newName);
	if (newName.empty() || univer)
	{
		return false;
	}
	
	univer = FindUniversity(oldName);
	if (!univer)
	{
		return false;
	}

	univer->SetName(newName);

	m_updated = true;

	return true;
}

bool CUniversityProcess::DeleteUniversity(const std::string name)
{
	const auto univer = FindUniversity(name);
	if (!univer)
	{
		return false;
	}

	m_students.erase(remove_if(m_students.begin(), m_students.end(), [&univer](shared_ptr<CStudent> student)
		{
			return (student->UniversityName().compare(univer->GetName()) == 0);
		})
		, m_students.end());

	m_universities.erase(find(m_universities.begin(), m_universities.end(),univer));

	m_updated = true;

	return true;
}

const students CUniversityProcess::GetListStudentsFromUniversity(const std::string universityName) const
{
	const auto univer = FindUniversity(universityName);
	if (!univer)
	{
		return students();
	}

	students findedStudents;
	auto it_beg = m_students.begin();
	auto it_end = m_students.end();
	for (; it_beg != it_end; it_beg++)
	{
		const CStudent *student = it_beg->get();
		if (student->UniversityName().compare(univer->GetName()) == 0)
		{
			findedStudents.push_back(*it_beg);
		}
	}

	return findedStudents;
}

bool CUniversityProcess::AddNewUniversity(const std::string newName)
{
	const auto univer = FindUniversity(newName);
	if (newName.empty() || univer)
	{
		return false;
	}

	m_universities.push_back(make_shared<CUniversity>(CUniversity(newName)));

	m_updated = true;

	return true;
}

std::shared_ptr<CUniversity> CUniversityProcess::FindUniversity(const std::string universityName) const
{
	if (m_universities.empty())
	{
		return false;
	}

	const auto it = find_if(m_universities.begin(), m_universities.end(), [&universityName](const shared_ptr<CUniversity>& university)
	{
		return university->GetName().compare(universityName) == 0;
	});

	return it != m_universities.end() ? *it : nullptr;
}

bool CUniversityProcess::UpdateStudentData(const int listNumber,
	const std::string name,
	const double growth,
	const double weight,
	const int age,
	const std::string universityName,
	const int numberOfYearsStudy)
{
	if ((size_t)listNumber > m_students.size() - 1)
	{
		return false;
	}

	auto student = m_students[listNumber];

	if (!name.empty())
	{
		student->SetName(name);
	}

	if (growth)
	{
		student->SetGrowth(growth);
	}

	if (weight)
	{
		student->SetWeight(weight);
	}

	if (age)
	{
		student->SetAge(age);
	}

	if (numberOfYearsStudy)
	{
		student->SetNumberOfYearsStudy(numberOfYearsStudy);
	}

	const auto univer = FindUniversity(universityName);
	if (univer)
	{
		student->SetUniversity(univer);
	}

	m_updated = true;

	return true;
}

bool CUniversityProcess::DeleteStudent(const int listNumber)
{
	if ((size_t)listNumber > m_students.size() - 1)
	{
		return false;
	}

	m_students.erase(m_students.begin() + listNumber);
	m_updated = true;

	return true;
}

bool CUniversityProcess::AddNewStudent(const std::string name,
									const std::string gender,
									const double growth,
									const double weight,
									const int age,
									const std::string university,
									const int numberOfYearsStudy)
{
	const auto univer = FindUniversity(university);
	if (name.empty() || !univer)
	{
		return false;
	}

	m_students.push_back(make_shared<CStudent>(name, gender, growth, weight, age, univer, numberOfYearsStudy));

	m_updated = true;

	return true;
}

bool CUniversityProcess::Updated()
{
	return m_updated;
}

std::string CUniversityProcess::ReadInputFile(const std::string fileName)
{
	ifstream inFile(fileName);
	inFile.exceptions(ios::badbit);

	string contentOfInFile((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
	inFile.close();

	return contentOfInFile;
}

void CUniversityProcess::ParseBaseData(std::string line, std::vector<std::string> &outValues)
{
	boost::regex expression("(?:\\s*(\\w+)\\s*\\[([^\\]]*)\\]\\s*)");
	boost::regex_split(back_inserter(outValues), line, expression);
}

void CUniversityProcess::ParseWordsSeparatedByCommas(std::string line, std::vector<std::string> &outValues)
{
	boost::regex expression("(?:\\s*\\\"([^\"]*)\\\"\\s*)"); /*([^, \\s]\\w + )*/
	boost::regex_split(back_inserter(outValues), line, expression);
}
