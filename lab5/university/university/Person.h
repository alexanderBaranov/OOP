#pragma once
#include <string>

enum class Gender
{
	Male,
	Female
};

class CPerson
{
public:
	CPerson(
		const std::string& name,
		Gender gender,
		double growth,
		double weight,
		int age);

	Gender GetGender() const;

	int GetAge() const;
	void SetAge(int newAge);

	const std::string& GetName() const;
	void SetName(const std::string& newName);

	double GetGrowth() const;
	void SetGrowth(double newGrowth);

	double GetWeight() const;
	void SetWeight(double newWeight);

private:
	Gender m_gender;
	std::string m_name;
	
	double m_growth;
	double m_weight;

	int m_age;
};

