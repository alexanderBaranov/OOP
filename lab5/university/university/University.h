#pragma once
#include <string>
#include <vector>
#include <memory>

class CStudent;

typedef std::shared_ptr<CStudent> CStudentPtr;
typedef std::vector<CStudentPtr> Students;

class CUniversity :public std::enable_shared_from_this<CUniversity>
{
public:
	CUniversity(std::string name);

	const std::string GetName() const;
	void SetName(const std::string& name);

	void AddStudent(const CStudentPtr& student);
	void RemoveStudent(const CStudentPtr& student);

	const Students& GetStudents();

private:
	std::string m_name;
	Students m_students;
};

