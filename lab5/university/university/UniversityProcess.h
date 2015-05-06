#pragma once
#include <memory>
#include <vector>
#include "University.h"
#include "Student.h"

//typedef std::vector<std::shared_ptr<CSubscriber>> subscribers;

class CUniversityProcess
{
public:
	CUniversityProcess(std::string listOfUniversity, std::string listOfStudents);
	~CUniversityProcess();

private:
	std::string ReadInputFile(const std::string fileName);
	void ParseBaseData(std::string line, std::vector<std::string> &outValues);
	void ParseWordsSeparatedByCommas(std::string line, std::vector<std::string> &outValues);

	void Load(std::string listOfUniversity, std::string listOfStudents);

	std::vector<std::shared_ptr<CUniversity>> m_universities;
	std::vector<std::shared_ptr<CStudent>> m_students;
	bool m_updateBD;
};

