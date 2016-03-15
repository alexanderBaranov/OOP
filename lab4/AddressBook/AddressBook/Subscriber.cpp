#include "stdafx.h"
#include "Subscriber.h"
#include <algorithm>
#include <boost/regex.hpp>
#include <boost/fusion/sequence/comparison/equal_to.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/cxx11/all_of.hpp>
#include <boost/algorithm/cxx11/any_of.hpp>

using namespace std;
using namespace boost::algorithm;

CSubscriber::CSubscriber()
{
}

CSubscriber::~CSubscriber()
{
}

void CSubscriber::SetName(const string& name)
{
	m_name = name;
}

const string& CSubscriber::GetName() const
{
	return m_name;
}

void CSubscriber::SetSurname(const string& surname)
{
	m_surname = surname;
}

const string& CSubscriber::GetSurname() const
{
	return m_surname;
}

void CSubscriber::SetPatronymic(const string& patronymic)
{
	m_patronymic = patronymic;
}

const string& CSubscriber::GetPatronymic() const
{
	return m_patronymic;
}

void CSubscriber::SetEmail(const string& email)
{
	vector<string> emails;
	ParseEmail(email, emails);
	m_email = emails;
}

string CSubscriber::GetEmail() const
{
	return GetStringObjectFromVector(m_email);
}

void CSubscriber::SetTelephoneNumber(const string& telephoneNumber)
{
	vector<string> telephoneNumbers;
	ParseTelephoneNumbers(telephoneNumber, telephoneNumbers);
	m_telephoneNumber = telephoneNumbers;
}

string CSubscriber::GetTelephoneNumber() const
{
	return GetStringObjectFromVector(m_telephoneNumber);
}

string CSubscriber::GetStringObjectFromVector(const vector<string>& objs) const
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

void CSubscriber::SetStreet(const string& street)
{
	m_street = street;
}

const string& CSubscriber::GetStreet() const
{
	return m_street;
}

void CSubscriber::SetHouse(const string& house)
{
	m_house = house;
}

const string& CSubscriber::GetHouse() const
{
	return  m_house;
}

void CSubscriber::SetApartment(const string& apartment)
{
	m_apartment = apartment;
}

const string& CSubscriber::GetApartment() const
{
	return m_apartment;
}

void CSubscriber::SetCity(const string& city)
{
	m_city = city;
}

const string& CSubscriber::GetCity() const
{
	return m_city;
}

vector<string> CSubscriber::ParseName(string line) const
{
	vector<string> values;
	boost::regex expression("([^\\s]+)");
	boost::regex_split(back_inserter(values), line, expression);

	return values;
}

vector<string> CSubscriber::ParseAddress(string line) const
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

bool CSubscriber::HasName(const string& name) const
{
	string lowercaseName(name);
	boost::algorithm::to_lower(lowercaseName);
	vector<string> names = lowercaseName.length() ? ParseName(lowercaseName) : vector<string>();

	string nameOfBD = m_name;
	boost::algorithm::to_lower(nameOfBD);

	string surnameOfBD = m_surname;
	boost::algorithm::to_lower(surnameOfBD);

	string patronymicOfBD = m_patronymic;
	boost::algorithm::to_lower(patronymicOfBD);

	vector<string>bdName({ nameOfBD, surnameOfBD, patronymicOfBD });

	return EqualVectors(names, bdName);
}

bool CSubscriber::HasAddress(const string& address) const
{
	string lowercaseAddress(address);
	boost::algorithm::to_lower(lowercaseAddress);
	vector<string> addresses = lowercaseAddress.length() ? ParseAddress(lowercaseAddress) : vector<string>();

	string street = m_street;
	boost::algorithm::to_lower(street);

	string house = m_house;
	boost::algorithm::to_lower(house);

	string apartment = m_apartment;
	boost::algorithm::to_lower(apartment);

	string city = m_city;
	boost::algorithm::to_lower(city);

	vector<string>bdAddresses({ street, house, apartment, city});

	return EqualVectors(addresses, bdAddresses);
}

bool CSubscriber::HasPhoneNumber(const string& telephoneNumber) const
{
	return any_of(m_telephoneNumber, bind2nd(equal_to<string>(), telephoneNumber));
}

bool CSubscriber::HasEmail(const string& email) const
{
	string lowercaseEmail(email);
	boost::algorithm::to_lower(lowercaseEmail);

	return any_of(m_email, bind2nd(equal_to<string>(), lowercaseEmail));
}

bool CSubscriber::EqualVectors(const vector<string>&vec, const vector<string>&bdVec) const
{
	if (vec.empty() || bdVec.empty())
	{
		return false;
	}

	return all_of(vec, [&](const string& strOfVector1){
		return any_of(bdVec, bind2nd(equal_to<string>(), strOfVector1));
	});

}