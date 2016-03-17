#include "stdafx.h"
#include "Student.h"

using namespace std;

static const int kMinYearsStudy = 1;
static const int kMaxYearsStudy = 5;

CStudent::CStudent(
				const string& name,
				Gender gender,
				double growth,
				double weight,
				int age,
				const weak_ptr<const CUniversity>& university,
				int numberOfYearsStudy)
	:CPerson(name, gender, growth, weight, age)
{
	SetNumberOfYearsStudy(numberOfYearsStudy);

	m_university = university;
}

int CStudent::GetNumberOfYearsStudy() const
{
	return m_numberOfYearsStudy;
}

const weak_ptr<const CUniversity>& CStudent::GetUniversity() const
{
	return m_university;
}

void CStudent::SetNumberOfYearsStudy(int year)
{
	if ((year >= kMinYearsStudy) && (year <= kMaxYearsStudy))
	{
		m_numberOfYearsStudy = year;
	}
}

void CStudent::SetUniversity(const std::shared_ptr<const CUniversity>& university)
{
	m_university = university;
}
