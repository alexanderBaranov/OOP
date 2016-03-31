#include "stdafx.h"
#include <algorithm>
#include "University.h"
#include <boost/range/algorithm/remove.hpp>
#include <boost/range/algorithm/remove_if.hpp>
#include "Student.h"

using namespace std;

CUniversity::CUniversity(string name)
:m_name(name)
{
}

const string CUniversity::GetName() const
{
	return m_name;
}


void CUniversity::SetName(const string name)
{
	m_name = name;
}

void CUniversity::AddStudent(const CStudentPtr& student)
{
	assert(student);

	if (student)
	{
		student->SetUniversity(shared_from_this());
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
	m_students.erase(boost::remove_if(m_students, [&](CStudentPtr& student) { return student->GetUniversity().get() != this; }), m_students.end());
	return m_students;
}