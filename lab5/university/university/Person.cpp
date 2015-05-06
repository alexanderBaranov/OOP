#include "stdafx.h"
#include "Person.h"

using namespace std;

CPerson::CPerson(const std::string name,
				const std::string gender,
				const double growth,
				const double weight,
				const int age)
	: m_age(age),
	m_gender(gender),
	m_name(name),
	m_growth(growth),
	m_weight(weight)
{
}


CPerson::~CPerson()
{
}


const std::string CPerson::Gender() const
{
	return m_gender;
}


const int CPerson::Age() const
{
	return m_age;
}

void CPerson::SetAge(const int newAge)
{
	if (newAge > m_age)
	{
		m_age = newAge;
	}
}

const std::string CPerson::Name() const
{
	return m_name;
}

void CPerson::SetName(const std::string newName)
{
	m_name = newName;
}

const double CPerson::Growth() const
{
	return m_growth;
}

void CPerson::SetGrowth(const double newGrowth)
{
	if (newGrowth > m_growth)
	{
		m_growth = newGrowth;
	}
}

const double CPerson::Weight() const
{
	return m_weight;
}


void CPerson::SetWeight(const double newWeight)
{
	m_weight = newWeight;
}
