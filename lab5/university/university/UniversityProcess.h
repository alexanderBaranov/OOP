#pragma once
#include <memory>
#include <vector>
#include "University.h"
#include "Student.h"

typedef std::vector<std::shared_ptr<CUniversity>> universites;
typedef std::vector<std::shared_ptr<CStudent>> students;

class CUniversityProcess
{
public:
	CUniversityProcess(const std::string listOfUniversity, const std::string listOfStudents);
	~CUniversityProcess();

	void Load(const std::string listOfUniversity, const std::string listOfStudents);
	
	const universites GetListUniversites() const;
	const students GetListStudents() const;
	
	bool ReplaceUniversity(const std::string oldName, const std::string newName);
	bool DeleteUniversity(const std::string name);

private:
	std::string ReadInputFile(const std::string fileName);
	void ParseBaseData(std::string line, std::vector<std::string> &outValues);
	void ParseWordsSeparatedByCommas(std::string line, std::vector<std::string> &outValues);
	std::shared_ptr<CUniversity> FindUniversity(const std::string universityName);

	universites m_universities;
	students m_students;
	bool m_updateBD;
};

