#pragma once
#include "Person.h"
#include <memory>
#include "University.h"

class CStudent :public CPerson
{
public:
	CStudent(const std::string& name, 
		Gender gender,
		double growth,
		double weight,
		int age,
		const std::weak_ptr<const CUniversity>& university,
		int numberOfYearsStudy);
	
	int GetNumberOfYearsStudy() const;
	void SetNumberOfYearsStudy(int year);

	const std::weak_ptr<const CUniversity>& GetUniversity() const;
	void SetUniversity(const std::shared_ptr<const CUniversity>& university);

private:
	std::weak_ptr<const CUniversity> m_university;
	int m_numberOfYearsStudy;
};

