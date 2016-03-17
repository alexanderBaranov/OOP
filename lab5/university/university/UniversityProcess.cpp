#include "stdafx.h"
#include "UniversityProcess.h"
#include <fstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/format.hpp>

using namespace std;

static const string NAME = "им€";
static const string GENDER = "пол";
static const string MALE = "м";
static const string FEMALE = "ж";
static const string AGE = "возраст";
static const string GROWTH = "рост";
static const string WEIGHT = "вес";
static const string UNIVERSITY = "университет";
static const string NUMBER_OF_YEARS_STUDY = "проучилс€";

CUniversityProcess::CUniversityProcess(const string& listOfUniversity, const string& listOfStudents)
	:m_universitiesFile(listOfUniversity),
	m_studentsFile(listOfStudents)
{
	Load(listOfUniversity, listOfStudents);
	m_updated = false;
}

void CUniversityProcess::Load(
	const string& listOfUniversity, 
	const string& listOfStudents)
{
	string contentListOfUniversity = ReadInputFile(listOfUniversity);
	vector<string> values;
	values = ParseWordsSeparatedByCommas(contentListOfUniversity);

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
	values = ParseDataBase(contentListOfStudents);

	for (size_t i = 0; i < values.size(); i++)
	{
		string name, age, growth, weight, university, numberOfYearsStudy;
		Gender gender;

		if (values[i] == NAME)
		{
			name = values[++i];
		}

		if (values[++i] == GENDER)
		{
			gender = GetEnumGenderFromString(values[++i]);
		}

		if (values[++i] == AGE)
		{
			age = values[++i];
		}

		if (values[++i] == GROWTH)
		{
			growth = values[++i];
		}

		if (values[++i] == WEIGHT)
		{
			weight = values[++i];
		}

		if (values[++i] == UNIVERSITY)
		{
			university = values[++i];
		}

		if (values[++i] == NUMBER_OF_YEARS_STUDY)
		{
			numberOfYearsStudy = values[++i];
		}

		const auto& univer = FindUniversity(university);
		if (univer)
		{
			univer->AddStudent(make_shared<CStudent>(name,
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
	
	ofstream outStudentsFile(m_studentsFile);
	outStudentsFile.exceptions(ios::badbit);

	for (const auto& univer : m_universities)
	{ 
		string str(univer->GetName());
		outUniversitiesFile << "\"" << str << "\"" << endl;

		for (const auto& student : univer->GetStudents())
		{
			string str;
			AppendProperty(str, NAME, student->GetName());
			AppendProperty(str, GENDER, GetStringFromEnumGender(student->GetGender()));
			AppendProperty(str, AGE, to_string(student->GetAge()));
			AppendProperty(str, GROWTH, to_string(student->GetGrowth()));
			AppendProperty(str, WEIGHT, to_string(student->GetWeight()));
			AppendProperty(str, UNIVERSITY, univer->GetName());
			AppendProperty(str, NUMBER_OF_YEARS_STUDY, to_string(student->GetNumberOfYearsStudy()));

			outStudentsFile << str << endl;
		}
	}

	outUniversitiesFile.close();

	outStudentsFile.close();

	m_updated = false;
}

string CUniversityProcess::GetStringFromEnumGender(Gender gender)
{
	string strGender;
	if (gender == Gender::Male)
	{
		strGender = MALE;
	}
	else if (gender == Gender::Female)
	{
		strGender = FEMALE;
	}

	return strGender;
}

Gender CUniversityProcess::GetEnumGenderFromString(const std::string& strGender)
{
	Gender gender = Gender::Male;
	if (strGender == FEMALE)
	{
		gender = Gender::Female;
	}

	return gender;
}

void CUniversityProcess::AppendProperty(string& str, const string& property, const string& value)
{
	str.append(property + "[" + value + "]");
}

const universites& CUniversityProcess::GetListUniversites() const
{
	return m_universities;
}

students CUniversityProcess::GetListStudents() const
{
	students students;

	for (const auto& univer : m_universities)
	{
		const auto& studentsFromUniver = univer->GetStudents();
		students.insert(students.end(), studentsFromUniver.begin(), studentsFromUniver.end());
	}

	return students;
}

bool CUniversityProcess::ReplaceUniversity(const string& oldName, const string& newName)
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

bool CUniversityProcess::DeleteUniversity(const string& name)
{
	const auto univer = FindUniversity(name);
	if (!univer)
	{
		return false;
	}

	//m_students.erase(remove_if(m_students.begin(), m_students.end(), [&univer](shared_ptr<CStudent> student)
	//	{
	//		return student->GetUniversity() == univer;
	//	})
	//	, m_students.end());

	m_universities.erase(find(m_universities.begin(), m_universities.end(),univer));

	m_updated = true;

	return true;
}

students CUniversityProcess::GetListStudentsFromUniversity(const string& universityName) const
{
	const auto univer = FindUniversity(universityName);
	if (!univer)
	{
		return students();
	}

	//students foundStudents;
	//auto it = copy_if(m_students.begin(), m_students.end(), back_inserter(foundStudents),
	//	[&](const shared_ptr<CStudent>& student)
	//{
	//	return student->GetUniversity() == univer;
	//});

	return univer->GetStudents();
}

bool CUniversityProcess::AddNewUniversity(const string& newName)
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

std::shared_ptr<CUniversity> CUniversityProcess::FindUniversity(const string& universityName) const
{
	if (m_universities.empty())
	{
		return nullptr;
	}

	const auto it = find_if(m_universities.begin(), m_universities.end(), [&universityName](const shared_ptr<CUniversity>& university)
	{
		return university->GetName() == universityName;
	});

	return it != m_universities.end() ? *it : nullptr;
}

bool CUniversityProcess::UpdateStudentData(
	int listNumber,
	const string& name,
	double growth,
	double weight,
	int age,
	const string& universityName,
	int numberOfYearsStudy)
{
	students students = GetListStudents();

	if ((size_t)listNumber > students.size() - 1)
	{
		return false;
	}

	bool studentUpdated = false;
	auto student = students.at(listNumber);

	if (!name.empty())
	{
		student->SetName(name);
		studentUpdated = true;
	}

	if (growth)
	{
		student->SetGrowth(growth);
		studentUpdated = true;
	}

	if (weight)
	{
		student->SetWeight(weight);
		studentUpdated = true;
	}

	if (age)
	{
		student->SetAge(age);
		studentUpdated = true;
	}

	if (numberOfYearsStudy)
	{
		student->SetNumberOfYearsStudy(numberOfYearsStudy);
		studentUpdated = true;
	}

	const auto& univer = FindUniversity(universityName);
	if (univer)
	{
		student->SetUniversity(univer);
		studentUpdated = true;
	}

	m_updated = studentUpdated;

	return studentUpdated;
}

bool CUniversityProcess::DeleteStudent(int listNumber)
{
	students students = GetListStudents();
	if ((size_t)listNumber > students.size() - 1)
	{
		return false;
	}

	auto student = students.at(listNumber);
	auto& univer = find_if(m_universities.begin(), m_universities.end(), [&](const shared_ptr<CUniversity>& univer)
	{
		return univer.get() == student->GetUniversity()._Get();
	});

	univer->get()->RemoveStudent(student);
	m_updated = true;

	return true;
}

bool CUniversityProcess::AddNewStudent(const string& name,
									const string& gender,
									double growth,
									double weight,
									int age,
									const string& university,
									int numberOfYearsStudy)
{
	const auto& univer = FindUniversity(university);
	if (name.empty() || !univer)
	{
		return false;
	}

	
	univer.get()->AddStudent(make_shared<CStudent>(name, GetEnumGenderFromString(gender), growth, weight, age, univer, numberOfYearsStudy));

	m_updated = true;

	return true;
}

bool CUniversityProcess::Updated()
{
	return m_updated;
}

string CUniversityProcess::ReadInputFile(const string& fileName)
{
	ifstream inFile(fileName);
	inFile.exceptions(ios::badbit);

	string contentOfInFile((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
	inFile.close();

	return contentOfInFile;
}

vector<string> CUniversityProcess::ParseDataBase(string line)
{
	vector<string> outValues;
	boost::regex expression("(?:\\s*(\\w+)\\s*\\[([^\\]]*)\\]\\s*)");
	boost::regex_split(back_inserter(outValues), line, expression);

	return outValues;
}

vector<string> CUniversityProcess::ParseWordsSeparatedByCommas(string line)
{
	vector<string> outValues;
	boost::regex expression("(?:\\s*\\\"([^\"]*)\\\"\\s*)"); /*([^, \\s]\\w + )*/
	boost::regex_split(back_inserter(outValues), line, expression);

	return outValues;
}
