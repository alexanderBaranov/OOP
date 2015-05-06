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
	std::string listOfUniversity, 
	std::string listOfStudents)
{
	string contentListOfUniversity = ReadInputFile(listOfUniversity);
	vector<string> values;
	ParseWordsSeparatedByCommas(contentListOfUniversity, values);

	for (const string& val : values)
	{
		m_universities.push_back(make_shared<CUniversity>(CUniversity(val)));
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



		m_students.push_back(make_shared<CStudent>(CStudent(

			)));
	}
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
