#pragma once
#include <string>
#include <vector>
#include <memory>

class CStudent;

typedef std::shared_ptr<CStudent> student;
typedef std::vector<std::shared_ptr<CStudent>> students;

class CUniversity
{
public:
	CUniversity(std::string name);

	const std::string GetName() const;
	void SetName(const std::string name);

	void AddStudent(student& student);
	void RemoveStudent(student& student);

	const students& GetStudents();

private:
	std::string m_name;
	students m_students;
};

