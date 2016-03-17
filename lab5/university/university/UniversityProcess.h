#pragma once
#include <memory>
#include <vector>
#include "University.h"
#include "Student.h"

typedef std::vector<std::shared_ptr<CUniversity>> universites;

class CUniversityProcess
{
public:
	CUniversityProcess(const std::string& listOfUniversity, const std::string& listOfStudents);

	void Load(const std::string& listOfUniversity, const std::string& listOfStudents);
	void Save();

	const universites& GetListUniversites() const;
	students GetListStudents() const;
	students GetListStudentsFromUniversity(const std::string& universityName) const;
	
	bool ReplaceUniversity(const std::string& oldName, const std::string& newName);
	
	bool DeleteUniversity(const std::string& name);
	bool DeleteStudent(int listNumber);

	bool AddNewUniversity(const std::string& newName);	
	bool AddNewStudent(const std::string& name,
					const std::string& gender,
					double growth,
					double weight,
					int age,
					const std::string& university,
					int numberOfYearsStudy);

	bool UpdateStudentData(int listNumber,
		const std::string& name,
		double growth,
		double weight,
		int age,
		const std::string& universityName,
		int numberOfYearsStudy);

	bool Updated();

	std::string GetStringFromEnumGender(Gender gender);
	Gender GetEnumGenderFromString(const std::string& strGender);
private:
	static std::string ReadInputFile(const std::string& fileName);
	static std::vector<std::string> CUniversityProcess::ParseDataBase(std::string line);
	std::vector<std::string> ParseWordsSeparatedByCommas(std::string line);
	std::shared_ptr<CUniversity> FindUniversity(const std::string& universityName) const;
	static void AppendProperty(
		std::string& str,
		const std::string& property,
		const std::string& value);

	universites m_universities;
	students m_students;
	bool m_updated;

	std::string m_universitiesFile;
	std::string m_studentsFile;
};

