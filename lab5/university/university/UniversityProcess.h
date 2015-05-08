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
	const students GetListStudentsFromUniversity(const std::string universityName) const;
	
	bool ReplaceUniversity(const std::string oldName, const std::string newName);
	
	bool DeleteUniversity(const std::string name);
	bool DeleteStudent(const int listNumber);

	bool AddNewUniversity(const std::string newName);

	
	bool UpdateStudentData(const int listNumber,
						const std::string name,
						const double growth,
						const double weight,
						const int age,
						const std::string universityName,
						const int numberOfYearsStudy);

	bool AddNewStudent(const std::string name,
					const std::string gender,
					const double growth,
					const double weight,
					const int age,
					const std::string university);

private:
	std::string ReadInputFile(const std::string fileName);
	void ParseBaseData(std::string line, std::vector<std::string> &outValues);
	void ParseWordsSeparatedByCommas(std::string line, std::vector<std::string> &outValues);
	std::shared_ptr<CUniversity> FindUniversity(const std::string universityName) const;

	universites m_universities;
	students m_students;
	bool m_updateBD;
};

