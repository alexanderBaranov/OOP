#pragma once
#include <string>
#include <vector>

class CSubscriber
{
public:
	CSubscriber();
	~CSubscriber();

	void SetName(const std::string& name);
	const std::string& GetName()  const;

	void SetSurname(const std::string& surname);
	const std::string& GetSurname()  const;

	void SetPatronymic(const std::string& patronymic);
	const std::string& GetPatronymic()  const;

	void SetEmail(const std::string& email);
	std::string GetEmail()  const;

	void SetTelephoneNumber(const std::string& telephoneNumber);
	std::string GetTelephoneNumber()  const;

	void SetStreet(const std::string& street);
	const std::string& GetStreet()  const;

	void SetHouse(const std::string& house);
	const std::string& GetHouse()  const;

	void SetApartment(const std::string& apartment);
	const std::string& GetApartment()  const;

	void SetCity(const std::string& city);
	const std::string& GetCity() const;

	bool HasName(const std::string& name) const;
	bool HasAddress(const std::string& address) const;
	bool HasPhoneNumber(const std::string& telephoneNumber) const;
	bool HasEmail(const std::string& email) const;

private:
	std::vector<std::string> ParseName(std::string line) const;
	std::vector<std::string> ParseAddress(std::string line) const;
	void ParseEmail(std::string line, std::vector<std::string>& outValues) const;
	void ParseTelephoneNumbers(std::string line, std::vector<std::string>& outValues) const;

	bool EqualVectors(const std::vector<std::string>&vec1, const std::vector<std::string>&vec2) const;
	
	std::string GetStringObjectFromVector(const std::vector<std::string>& objs) const;

	int m_index;
	std::string m_name;
	std::string m_surname;
	std::string m_patronymic;
	std::vector<std::string> m_email;
	std::vector<std::string> m_telephoneNumber;
	std::string m_street;
	std::string m_house;
	std::string m_apartment;
	std::string m_city;
};

