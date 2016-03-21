#include "stdafx.h"
#include <algorithm>
#include "University.h"
#include <boost/range/algorithm/remove.hpp>

CUniversity::CUniversity(std::string name)
:m_name(name)
{
}

const std::string CUniversity::GetName() const
{
	return m_name;
}


void CUniversity::SetName(const std::string name)
{
	m_name = name;
}

void CUniversity::AddStudent(const CStudentPtr& student)
{
	assert(student);

	if (student)
	{
		m_students.push_back(student);
	}
}

void CUniversity::RemoveStudent(const CStudentPtr& student)
{
	assert(student);

	if (student)
	{
		m_students.erase(boost::remove(m_students, student), m_students.end());
	}
}

const Students& CUniversity::GetStudents()
{
	return m_students;
}