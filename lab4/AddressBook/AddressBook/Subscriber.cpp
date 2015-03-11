#include "stdafx.h"
#include "Subscriber.h"
#include <algorithm>
#include <boost/regex.hpp>
#include <boost/fusion/sequence/comparison/equal_to.hpp>

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

int CSubscriber::GetIndex()
{
	return m_index;
}

void CSubscriber::SetName(string name)
{
	m_name = name;
}

void CSubscriber::SetSurname(string surname)
{
	m_surname = surname;
}

void CSubscriber::SetPatronymic(string patronymic)
{
	m_patronymic = patronymic;
}

void CSubscriber::SetEmail(string email)
{
	vector<string> emails;
	ParseEmail(email, emails);
	m_email = emails;
}

void CSubscriber::SetTelephoneNumber(string telephoneNumber)
{
	vector<string> telephoneNumbers;
	ParseTelephoneNumbers(telephoneNumber, telephoneNumbers);
	m_telephoneNumber = telephoneNumbers;
}

void CSubscriber::SetStreet(string street)
{
	m_street = street;
}

void CSubscriber::SetHouse(string house)
{
	m_house = house;
}

void CSubscriber::SetApartment(string apartment)
{
	m_apartment = apartment;
}

void CSubscriber::SetCity(string city)
{
	m_city = city;
}

void CSubscriber::SetRepublic(string republic)
{
	m_republic = republic;
}

void CSubscriber::SetCountry(string country)
{
	m_country = country;
}

vector<string> CSubscriber::ParseFindString(string line)
{
	vector<string> values;
	boost::regex expression("(\\w+)");
	boost::regex_split(back_inserter(values), line, expression);

	return values;
}

void CSubscriber::ParseEmail(string line, vector<string> &outValues)
{
	boost::regex expression("([^,\\s]+)");
	boost::regex_split(back_inserter(outValues), line, expression);
}

void CSubscriber::ParseTelephoneNumbers(string line, vector<string> &outValues)
{
	boost::regex expression("([^,\\s]+)");
	boost::regex_split(back_inserter(outValues), line, expression);
}


bool CSubscriber::FindByName(string name)
{
	vector<string> names = name.length() ? ParseFindString(name) : vector<string>();
	vector<string>bdName({ m_name, m_surname, m_patronymic });

	return CompareVectors(names, bdName);
}

bool CSubscriber::FindByAddress(string address)
{
	vector<string> addresses = address.length() ? ParseFindString(address) : vector<string>();
	vector<string>bdAddresses({ m_street, m_house, m_apartment, m_city, m_republic, m_country });

	return CompareVectors(addresses, bdAddresses);
}

bool CSubscriber::FindByTelephoneNumber(string telephoneNumber)
{
	return find(m_telephoneNumber.begin(), m_telephoneNumber.end(), telephoneNumber) != m_telephoneNumber.end();
}

bool CSubscriber::FindByEmail(string email)
{
	return find(m_email.begin(), m_email.end(), email) != m_email.end();;
}

bool CSubscriber::CompareVectors(const vector<string>&vec, const vector<string>&bdVec)
{
	int countOfEquals = 0;
	for_each(vec.begin(), vec.end(), [&countOfEquals, &bdVec](string str)
	{
		if (find(bdVec.begin(), bdVec.end(), str) != bdVec.end()){
			countOfEquals++;
		}
	});

	return countOfEquals == vec.size();
}