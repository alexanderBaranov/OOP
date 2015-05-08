#include "stdafx.h"
#include "Student.h"

using namespace std;

static const int kMinYearsStudy = 1;
static const int kMaxYearsStudy = 5;

CStudent::CStudent(const std::string name, 
	const std::string gender,
	const double growth,
	const double weight,
	const int age,
	const std::shared_ptr<CUniversity> university)
:CPerson(name, gender, growth, weight, age),
m_university(university)
{
}

CStudent::~CStudent()
{
}

const int CStudent::NumberOfYearsStudy() const
{
	return m_numberOfYearsStudy;
}

const std::string CStudent::UniversityName() const
{
	return m_university->GetName();
}

void CStudent::SetNumberOfYearsStudy(const int year)
{
	if ((year >= kMinYearsStudy) && (year <= kMaxYearsStudy))
	{
		m_numberOfYearsStudy = year;
	}
}

void CStudent::SetUniversity(const std::shared_ptr<CUniversity> university)
{
	m_university = university;
}