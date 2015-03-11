#pragma once
#include <string>
#include <vector>

class CSubscriber
{
public:
	CSubscriber();
	~CSubscriber();

	void SetIndex(std::string index);
	int GetIndex();

	void SetName(std::string name);
	void SetSurname(std::string surname);
	void SetPatronymic(std::string patronymic);
	void SetEmail(std::string email);
	void SetTelephoneNumber(std::string telephoneNumber);
	void SetStreet(std::string street);
	void SetHouse(std::string house);
	void SetApartment(std::string apartment);
	void SetCity(std::string city);
	void SetRepublic(std::string republic);
	void SetCountry(std::string country);

	bool FindByName(std::string name);
	bool FindByAddress(std::string address);
	bool FindByTelephoneNumber(std::string telephoneNumber);
	bool FindByEmail(std::string email);

private:
	std::vector<std::string> ParseFindString(std::string line);
	bool CSubscriber::CompareVectors(const std::vector<std::string>&vec1, const std::vector<std::string>&vec2);
	void ParseEmail(std::string line, std::vector<std::string> &outValues);
	void ParseTelephoneNumbers(std::string line, std::vector<std::string> &outValues);

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
	std::string m_republic;
	std::string m_country;
};

