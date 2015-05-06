#pragma once
#include "Person.h"
#include <memory>
#include "University.h"

class CStudent :public CPerson
{
public:
	CStudent(const std::string name, 
		const std::string gender,
		const double growth,
		const double weight,
		const int age,
		const std::shared_ptr<CUniversity> university);

	~CStudent();
	
	const int NumberOfYearsStudy() const;
	const std::string UniversityName() const;
	void SetNumberOfYearsStudy(const int year);

private:
	const std::shared_ptr<CUniversity> m_university;
	int m_numberOfYearsStudy;
};

