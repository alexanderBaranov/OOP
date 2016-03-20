#include "stdafx.h"
#include "Student.h"

using namespace std;

static const int MIN_YEARS_STUDY = 1;
static const int MAX_YEARS_STUDY = 5;

CStudent::CStudent(
				const string& name,
				Gender gender,
				double growth,
				double weight,
				int age,
				const shared_ptr<const CUniversity>& university,
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

shared_ptr<const CUniversity> CStudent::GetUniversity() const
{
	return m_university.lock();
}

void CStudent::SetNumberOfYearsStudy(int year)
{
	if ((year >= MIN_YEARS_STUDY) && (year <= MAX_YEARS_STUDY))
	{
		m_numberOfYearsStudy = year;
	}
}

void CStudent::SetUniversity(const std::shared_ptr<const CUniversity>& university)
{
	m_university = university;
}
