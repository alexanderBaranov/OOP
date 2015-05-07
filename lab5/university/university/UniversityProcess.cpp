#include "stdafx.h"
#include "UniversityProcess.h"
#include <fstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/format.hpp>

using namespace std;

static const string kName = "имя";
static const string kGender = "пол";
static const string kAge = "возраст";
static const string kGrowth = "рост";
static const string kWeight = "вес";
static const string kUniversity = "университет";

CUniversityProcess::CUniversityProcess(
	std::string listOfUniversity, 
	std::string listOfStudents)
{
	Load(listOfUniversity, listOfStudents);
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
		if (!FindUniversity(val))
		{
			m_universities.push_back(make_shared<CUniversity>(CUniversity(val)));
		}
	}

	string contentListOfStudents = ReadInputFile(listOfStudents);
	ParseWordsSeparatedByCommas(contentListOfStudents, values);

	for (size_t i = 0; i < values.size(); i++)
	{
		string name, gender, age, growth, weight, university;

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

		const auto univer = FindUniversity(university);
		if (univer)
		{
			m_students.push_back(make_shared<CStudent>(name, gender, stod(growth), stod(weight), stoi(age), univer));
		}
	}
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
	auto it = FindUniversity(newName);
	if (it)
	{
		return false;
	}
	
	it = FindUniversity(oldName);
	if (!it)
	{
		return false;
	}

	it->SetName(newName);

	return true;
}

bool CUniversityProcess::DeleteUniversity(const std::string name)
{
	const auto univer_it = FindUniversity(name);
	if (!univer_it)
	{
		return false;
	}

	auto it_beg = m_students.begin();
	auto it_end = m_students.end();
	for (; it_beg != it_end; it_beg)
	{
		const CStudent *student = it_beg->get();
		if (student->UniversityName().compare(univer_it->GetName()) == 0)
		{
			it_beg = m_students.erase(it_beg);
		}
	}

	m_universities.erase(find(m_universities.begin(), m_universities.end(),univer_it));

	return true;
}

std::shared_ptr<CUniversity> CUniversityProcess::FindUniversity(const std::string universityName)
{
	if (m_universities.empty())
	{
		return false;
	}

	const auto it = find_if(m_universities.begin(), m_universities.end(), [&universityName](const shared_ptr<CUniversity>& university)
	{
		return university->GetName().compare(universityName) == 0;
	});

	return *it;
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
	boost::regex expression("([^,\\s]+)");
	boost::regex_split(back_inserter(outValues), line, expression);
}
