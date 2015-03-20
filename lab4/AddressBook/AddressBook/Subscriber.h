#pragma once
#include <string>
#include <vector>

class CSubscriber
{
public:
	CSubscriber();
	~CSubscriber();

	void SetIndex(std::string index);
	int GetIndex() const;

	void SetName(std::string name);
	std::string GetName()  const;

	void SetSurname(std::string surname);
	std::string GetSurname()  const;

	void SetPatronymic(std::string patronymic);
	std::string GetPatronymic()  const;

	void SetEmail(std::string email);
	std::string GetEmail()  const;

	void SetTelephoneNumber(std::string telephoneNumber);
	std::string GetTelephoneNumber()  const;

	void SetStreet(std::string street);
	std::string GetStreet()  const;

	void SetHouse(std::string house);
	std::string GetHouse()  const;

	void SetApartment(std::string apartment);
	std::string GetApartment()  const;

	void SetCity(std::string city);
	std::string GetCity() const;

	bool FindByName(std::string name);
	bool FindByAddress(std::string address);
	bool FindByTelephoneNumber(std::string telephoneNumber);
	bool FindByEmail(std::string email);

private:
	std::vector<std::string> CSubscriber::ParseName(std::string line);
	std::vector<std::string> ParseAddress(std::string line);
	void ParseEmail(std::string line, std::vector<std::string> &outValues);
	void ParseTelephoneNumbers(std::string line, std::vector<std::string> &outValues);

	bool CompareVectors(const std::vector<std::string>&vec1, const std::vector<std::string>&vec2);
	
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

