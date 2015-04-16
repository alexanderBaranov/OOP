#include "stdafx.h"
#include "Subscriber.h"
#include <algorithm>
#include <boost/regex.hpp>
#include <boost/fusion/sequence/comparison/equal_to.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

CSubscriber::CSubscriber()
{
}

CSubscriber::~CSubscriber()
{
}

void CSubscriber::SetIndex(string index)
{
	m_index = stoi(index);
}

int const& CSubscriber::GetIndex() const
{
	return m_index;
}

void CSubscriber::SetName(string name)
{
	m_name = name;
}

string const& CSubscriber::GetName() const
{
	return m_name;
}

void CSubscriber::SetSurname(string surname)
{
	m_surname = surname;
}

string const& CSubscriber::GetSurname() const
{
	return m_surname;
}

void CSubscriber::SetPatronymic(string patronymic)
{
	m_patronymic = patronymic;
}

string const& CSubscriber::GetPatronymic() const
{
	return m_patronymic;
}

void CSubscriber::SetEmail(string email)
{
	vector<string> emails;
	ParseEmail(email, emails);
	m_email = emails;
}

string const CSubscriber::GetEmail() const
{
	return GetStringObjectFromVector(m_email);
}

void CSubscriber::SetTelephoneNumber(string telephoneNumber)
{
	vector<string> telephoneNumbers;
	ParseTelephoneNumbers(telephoneNumber, telephoneNumbers);
	m_telephoneNumber = telephoneNumbers;
}

string const CSubscriber::GetTelephoneNumber() const
{
	return GetStringObjectFromVector(m_telephoneNumber);
}

string const CSubscriber::GetStringObjectFromVector(const vector<string>& objs) const
{
	string strObjs;

	for (size_t i = 0; i < objs.size(); i++)
	{
		if (i)
		{
			strObjs.append(", ");
		}
		strObjs.append(objs[i]);
	}

	return strObjs;
}

void CSubscriber::SetStreet(string street)
{
	m_street = street;
}

string const& CSubscriber::GetStreet() const
{
	return m_street;
}

void CSubscriber::SetHouse(string house)
{
	m_house = house;
}

string const& CSubscriber::GetHouse() const
{
	return  m_house;
}

void CSubscriber::SetApartment(string apartment)
{
	m_apartment = apartment;
}

string const& CSubscriber::GetApartment() const
{
	return m_apartment;
}

void CSubscriber::SetCity(string city)
{
	m_city = city;
}

string const& CSubscriber::GetCity() const
{
	return m_city;
}

vector<string> const CSubscriber::ParseName(string line) const
{
	vector<string> values;
	boost::regex expression("([^\\s]+)");
	boost::regex_split(back_inserter(values), line, expression);

	return values;
}

vector<string> const CSubscriber::ParseAddress(string line) const
{
	vector<string> values;
	boost::regex expression("\\s*([^,]+)\\s*");
	boost::regex_split(back_inserter(values), line, expression);

	return values;
}

void CSubscriber::ParseEmail(string line, vector<string> &outValues) const
{
	boost::regex expression("([^,\\s]+)");
	boost::regex_split(back_inserter(outValues), line, expression);
}

void CSubscriber::ParseTelephoneNumbers(string line, vector<string> &outValues) const
{
	boost::regex expression("([^,\\s]+)");
	boost::regex_split(back_inserter(outValues), line, expression);
}


bool CSubscriber::FindByName(string name) const
{
	boost::algorithm::to_lower(name);
	vector<string> names = name.length() ? ParseName(name) : vector<string>();

	string nameOfBD = m_name;
	boost::algorithm::to_lower(nameOfBD);

	string surnameOfBD = m_surname;
	boost::algorithm::to_lower(surnameOfBD);

	string patronymicOfBD = m_patronymic;
	boost::algorithm::to_lower(patronymicOfBD);

	vector<string>bdName({ nameOfBD, surnameOfBD, patronymicOfBD });

	return CompareVectors(names, bdName);
}

bool CSubscriber::FindByAddress(string address) const
{
	boost::algorithm::to_lower(address);
	vector<string> addresses = address.length() ? ParseAddress(address) : vector<string>();

	string street = m_street;
	boost::algorithm::to_lower(street);

	string house = m_house;
	boost::algorithm::to_lower(house);

	string apartment = m_apartment;
	boost::algorithm::to_lower(apartment);

	string city = m_city;
	boost::algorithm::to_lower(city);

	vector<string>bdAddresses({ street, house, apartment, city});

	return CompareVectors(addresses, bdAddresses);
}

bool CSubscriber::FindByTelephoneNumber(string telephoneNumber) const
{
	return find(m_telephoneNumber.begin(), m_telephoneNumber.end(), telephoneNumber) != m_telephoneNumber.end();
}

bool CSubscriber::FindByEmail(string email) const
{
	boost::algorithm::to_lower(email);

	vector<string> temp;
	for each (string email in m_email)
	{
		boost::algorithm::to_lower(email);
		temp.push_back(email);
	}

	return find(temp.begin(), temp.end(), email) != temp.end();
}

bool CSubscriber::CompareVectors(const vector<string>&vec, const vector<string>&bdVec) const
{
	if (vec.empty() || bdVec.empty())
	{
		return false;
	}

	int countOfEquals = 0;
	for_each(vec.begin(), vec.end(), [&countOfEquals, &bdVec](string str)
	{
		if (find(bdVec.begin(), bdVec.end(), str) != bdVec.end()){
			countOfEquals++;
		}
	});

	return countOfEquals == vec.size();
}