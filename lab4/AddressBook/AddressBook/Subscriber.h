#pragma once
#include <string>
#include <vector>

class CSubscriber
{
public:
	CSubscriber();
	~CSubscriber();

	void SetIndex(std::string index);
	int const& GetIndex() const;

	void SetName(std::string name);
	std::string const& GetName()  const;

	void SetSurname(std::string surname);
	std::string const& GetSurname()  const;

	void SetPatronymic(std::string patronymic);
	std::string const& GetPatronymic()  const;

	void SetEmail(std::string email);
	std::string const GetEmail()  const;

	void SetTelephoneNumber(std::string telephoneNumber);
	std::string const GetTelephoneNumber()  const;

	void SetStreet(std::string street);
	std::string const& GetStreet()  const;

	void SetHouse(std::string house);
	std::string const& GetHouse()  const;

	void SetApartment(std::string apartment);
	std::string const& GetApartment()  const;

	void SetCity(std::string city);
	std::string const& GetCity() const;

	bool FindByName(std::string name) const;
	bool FindByAddress(std::string address) const;
	bool FindByTelephoneNumber(std::string telephoneNumber) const;
	bool FindByEmail(std::string email) const;

private:
	std::vector<std::string> const CSubscriber::ParseName(std::string line) const;
	std::vector<std::string> const ParseAddress(std::string line) const;
	void ParseEmail(std::string line, std::vector<std::string> &outValues) const;
	void ParseTelephoneNumbers(std::string line, std::vector<std::string> &outValues) const;

	bool CompareVectors(const std::vector<std::string>&vec1, const std::vector<std::string>&vec2) const;
	
	std::string const GetStringObjectFromVector(const std::vector<std::string>& objs) const;

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

