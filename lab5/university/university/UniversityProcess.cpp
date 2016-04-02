#include "stdafx.h"
#include "UniversityProcess.h"
#include <fstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>

using namespace std;

static const string NAME = "имя";
static const string GENDER = "пол";
static const string MALE = "м";
static const string FEMALE = "ж";
static const string AGE = "возраст";
static const string GROWTH = "рост";
static const string WEIGHT = "вес";
static const string UNIVERSITY = "университет";
static const string NUMBER_OF_YEARS_STUDY = "проучился";

static int MIN_GROWTH = 50;
static int MIN_WEIGHT = 6;

CUniversityManagement::CUniversityManagement(const string& fileNameOfUniversites, const string& fileNameOfStudents)
{
	LoadListsStudentsAndUniversitesFromFiles(fileNameOfUniversites, fileNameOfStudents);
}

void CUniversityManagement::LoadListsStudentsAndUniversitesFromFiles(
	const string& fileNameOfUniversites,
	const string& fileNameOfStudents)
{
	if (!boost::filesystem::exists(fileNameOfUniversites)
		|| !boost::filesystem::exists(fileNameOfStudents))
	{
		throw exception("File with list of universites or list of students not exist");
	}

	m_updated = false;

	m_universitiesFile = fileNameOfUniversites;
	m_studentsFile = fileNameOfStudents;

	string contentListOfUniversity = ReadInputFile(m_universitiesFile);
	vector<string> values;
	values = ParseWordsSeparatedByCommas(contentListOfUniversity);

	m_universities.clear();

	for (const string& val : values)
	{
		const auto univer = FindUniversity(val);
		if (!FindUniversity(val))
		{
			m_universities.push_back(make_shared<CUniversity>(CUniversity(val)));
		}
	}

	values.clear();

	ifstream inFileOfStudents(m_studentsFile);
	inFileOfStudents.exceptions(ios::badbit);

	string lineOfFile;
	while (getline(inFileOfStudents, lineOfFile))
	{
		vector<string> values = ParseDataBase(lineOfFile);

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
}

void CUniversityManagement::SaveChanges()
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

	m_updated = false;
}

void CUniversityManagement::AppendProperty(string& str, const string& property, const string& value)
{
	str.append(property + "[" + value + "]");
}

const Universites& CUniversityManagement::GetUniversites() const
{
	return m_universities;
}

Students CUniversityManagement::GetStudents() const
{
	Students students;

	for (const auto& univer : m_universities)
	{
		const auto& studentsFromUniver = univer->GetStudents();
		students.insert(students.end(), studentsFromUniver.begin(), studentsFromUniver.end());
	}

	return students;
}

bool CUniversityManagement::RenameUniversity(const string& oldName, const string& newName)
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

bool CUniversityManagement::DeleteUniversity(const string& name)
{
	const auto univer = FindUniversity(name);
	if (!univer)
	{
		return false;
	}

	m_universities.erase(find(m_universities.begin(), m_universities.end(),univer));

	m_updated = true;

	return true;
}

Students CUniversityManagement::GetStudentsFromUniversity(const string& universityName) const
{
	const auto univer = FindUniversity(universityName);
	if (!univer)
	{
		return Students();
	}

	return univer->GetStudents();
}

bool CUniversityManagement::AddNewUniversity(const string& newName)
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

CUniversityPtr CUniversityManagement::FindUniversity(const string& universityName) const
{
	if (m_universities.empty())
	{
		return nullptr;
	}

	const auto it = find_if(m_universities.begin(), m_universities.end(), [&universityName](const CUniversityPtr& university)
	{
		return university->GetName() == universityName;
	});

	return it != m_universities.end() ? *it : nullptr;
}

bool CUniversityManagement::UpdateStudentData(
	int listNumber,
	const string& name,
	double growth,
	double weight,
	int age,
	const string& universityName,
	int numberOfYearsStudy,
	string& error)
{
	Students students = GetStudents();

	if ((size_t)listNumber > students.size() - 1)
	{
		error = "Студент не найден.";
		return false;
	}

	auto student = students.at(listNumber);
	bool studentUpdated = false;

	const auto& univer = FindUniversity(universityName);
	if (univer)
	{
		univer->AddStudent(student);

		studentUpdated = true;
	}
	else if (!universityName.empty())
	{
		error = "Такой университет не существует.";
		return false;
	}

	if (growth >= MIN_GROWTH)
	{
		student->SetGrowth(growth);
		studentUpdated = true;
	}
	else
	{
		error = "Рост студента должен быть больше " + to_string(MIN_GROWTH) + " см.";
		return false;
	}

	if (weight >= MIN_WEIGHT)
	{
		student->SetWeight(weight);
		studentUpdated = true;
	}
	else
	{
		error = "Вес студента должен быть больше " + to_string(MIN_WEIGHT) + " кг.";
		return false;
	}

	if (!name.empty())
	{
		student->SetName(name);
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

	m_updated = studentUpdated;

	return studentUpdated;
}

bool CUniversityManagement::DeleteStudent(int listNumber)
{
	Students students = GetStudents();
	if ((size_t)listNumber >= students.size())
	{
		return false;
	}

	auto student = students.at(listNumber);
	auto& univer = find_if(m_universities.begin(), m_universities.end(), [&](const shared_ptr<CUniversity>& univer)
	{
		return univer == student->GetUniversity();
	});

	if (univer != m_universities.end())
	{
		(*univer)->RemoveStudent(student);
		m_updated = true;
	}
	else
	{
		return false;
	}

	return true;
}

bool CUniversityManagement::AddNewStudent(const string& name,
									Gender gender,
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

	
	univer.get()->AddStudent(make_shared<CStudent>(name, gender, growth, weight, age, univer, numberOfYearsStudy));

	m_updated = true;

	return true;
}

bool CUniversityManagement::Updated() const
{
	return m_updated;
}

string CUniversityManagement::ReadInputFile(const string& fileName)
{
	ifstream inFile(fileName);
	inFile.exceptions(ios::badbit);

	string contentOfInFile((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
	inFile.close();

	return contentOfInFile;
}

vector<string> CUniversityManagement::ParseDataBase(string line)
{
	vector<string> outValues;
	boost::regex expression("(?:\\s*(\\w+)\\s*\\[([^\\]]*)\\]\\s*)");
	boost::regex_split(back_inserter(outValues), line, expression);

	return outValues;
}

vector<string> CUniversityManagement::ParseWordsSeparatedByCommas(string line)
{
	vector<string> outValues;
	boost::regex expression("(?:\\s*\\\"([^\"]*)\\\"\\s*)"); /*([^, \\s]\\w + )*/
	boost::regex_split(back_inserter(outValues), line, expression);

	return outValues;
}

string GetStringFromEnumGender(Gender gender)
{
	string strGender = "";
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

Gender GetEnumGenderFromString(const std::string& strGender)
{
	Gender gender = Gender::Unknown;
	if (strGender == FEMALE)
	{
		gender = Gender::Female;
	}
	else if (strGender == MALE)
	{
		gender = Gender::Male;
	}

	return gender;
}
