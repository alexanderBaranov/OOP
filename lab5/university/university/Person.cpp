#include "stdafx.h"
#include "Person.h"

using namespace std;

CPerson::CPerson(
				const std::string& name,
				Gender gender,
				double growth,
				double weight,
				int age)
	: m_age(age),
	m_gender(gender),
	m_name(name),
	m_growth(growth),
	m_weight(weight)
{
}

Gender CPerson::GetGender() const
{
	return m_gender;
}


int CPerson::GetAge() const
{
	return m_age;
}

void CPerson::SetAge(int newAge)
{
	if (newAge > m_age)
	{
		m_age = newAge;
	}
}

const string& CPerson::GetName() const
{
	return m_name;
}

void CPerson::SetName(const string& newName)
{
	m_name = newName;
}

double CPerson::GetGrowth() const
{
	return m_growth;
}

void CPerson::SetGrowth(double newGrowth)
{
	if (newGrowth > m_growth)
	{
		m_growth = newGrowth;
	}
}

double CPerson::GetWeight() const
{
	return m_weight;
}


void CPerson::SetWeight(double newWeight)
{
	m_weight = newWeight;
}
