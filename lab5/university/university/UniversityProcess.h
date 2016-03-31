#pragma once
#include <memory>
#include <vector>
#include "University.h"
#include "Student.h"

typedef std::shared_ptr<CUniversity> CUniversityPtr;
typedef std::vector<CUniversityPtr> Universites;

std::string GetStringFromEnumGender(Gender gender);
Gender GetEnumGenderFromString(const std::string& strGender);

class CUniversityManagement
{
public:
	CUniversityManagement(const std::string& fileNameOfUniversites, const std::string& fileNameOfStudents);
	CUniversityManagement() = default;

	void LoadListsStudentsAndUniversitesFromFiles(
		const std::string& fileNameOfUniversites,
		const std::string& fileNameOfStudents);

	void SaveChanges();

	const Universites& GetUniversites() const;
	Students GetStudents() const;
	Students GetStudentsFromUniversity(const std::string& universityName) const;
	
	bool RenameUniversity(const std::string& oldName, const std::string& newName);
	
	bool DeleteUniversity(const std::string& name);
	bool DeleteStudent(int listNumber);

	bool AddNewUniversity(const std::string& newName);	
	bool AddNewStudent(const std::string& name,
					Gender gender,
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
		int numberOfYearsStudy,
		std::string& error);

	bool Updated() const;

private:
	static std::string ReadInputFile(const std::string& fileName);
	static std::vector<std::string> ParseDataBase(std::string line);
	std::vector<std::string> ParseWordsSeparatedByCommas(std::string line);
	CUniversityPtr FindUniversity(const std::string& universityName) const;
	static void AppendProperty(
		std::string& str,
		const std::string& property,
		const std::string& value);

	Universites m_universities;
	Students m_students;
	bool m_updated;

	std::string m_universitiesFile;
	std::string m_studentsFile;
};

