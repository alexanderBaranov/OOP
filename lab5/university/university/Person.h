#pragma once
#include <string>

class CPerson
{
public:
	CPerson(
		const std::string name,
		const std::string gender,
		const double growth,
		const double weight,
		const int age);

	~CPerson();

	const std::string Gender() const;
	
	const int Age() const;
	void SetAge(const int newAge);
	
	const std::string Name() const;
	void SetName(const std::string newName);

	const double Growth() const;
	void SetGrowth(const double newGrowth);

	const double Weight() const;
	void SetWeight(const double newWeight);

private:
	std::string m_gender;
	std::string m_name;
	
	double m_growth;
	double m_weight;

	int m_age;
};

