#include "stdafx.h"
#include <algorithm>
#include "University.h"


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

void CUniversity::AddStudent(student& student)
{
	if (student)
	{
		m_students.push_back(student);
	}
}

void CUniversity::RemoveStudent(student& stud)
{
	if (stud)
	{
		remove_if(m_students.begin(), m_students.end(), [&](student& s)
		{
			return s == stud;
		});
	}
}

const students& CUniversity::GetStudents()
{
	return m_students;
}