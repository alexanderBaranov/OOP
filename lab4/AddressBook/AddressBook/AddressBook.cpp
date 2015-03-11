// AddressBook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AddressBook.h"
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

using namespace std;

static const string kBaseData = "BaseData.txt";
static const int kColumn = 10;

static const string kIndex = "индекс";
static const string kName = "имя";
static const string kSurname = "фамилие";
static const string kPatronymic = "отчество";
static const string kEmail = "email";
static const string kTelephoneNumber = "телефон";
static const string kStreet = "улица";
static const string kHouse = "дом";
static const string kApartment = "квартира";
static const string kCity = "город";
static const string kRepublic = "республика";
static const string kCountry = "страна";

CAddressBook::CAddressBook()
{
	LoadSubscribers();
}

CAddressBook::~CAddressBook()
{
	SaveSubscribers();
}

void CAddressBook::LoadSubscribers()
{
	string contentBD = ReadInputFile(kBaseData);
	vector<string> values;
	ParseBaseData(contentBD, values);

	for (size_t i = 0; i < values.size(); i++)
	{
		auto subscriber= make_shared<CSubscriber>();

		if (values[i] == kIndex)
		{
			subscriber->SetIndex(values[++i]);
		}
		
		if (values[++i] == kName)
		{
			subscriber->SetName(values[++i]);
		}
		
		if (values[++i] == kSurname)
		{
			subscriber->SetSurname(values[++i]);
		}
		
		if (values[++i] == kPatronymic)
		{
			subscriber->SetPatronymic(values[++i]);
		}
		
		if (values[++i] == kEmail)
		{
			subscriber->SetEmail(values[++i]);
		}
		
		if (values[++i] == kTelephoneNumber)
		{
			subscriber->SetTelephoneNumber(values[++i]);
		}
		
		if (values[++i] == kStreet)
		{
			subscriber->SetStreet(values[++i]);
		}
		
		if (values[++i] == kHouse)
		{
			subscriber->SetHouse(values[++i]);
		}
		
		if (values[++i] == kApartment)
		{
			subscriber->SetApartment(values[++i]);
		}
		
		if (values[++i] == kCity)
		{
			subscriber->SetCity(values[++i]);
		}
		
		if (values[++i] == kRepublic)
		{
			subscriber->SetRepublic(values[++i]);
		}
		
		if (values[++i] == kCountry)
		{
			subscriber->SetCountry(values[++i]);
		}

		m_subscribers.push_back(move(subscriber));
	}
}

void CAddressBook::SaveSubscribers()
{
	if (m_updateBD)
	{
		ofstream outFile(kBaseData);
		outFile.exceptions(ios::badbit);

		for (const auto& subscriber : m_subscribers)
		{
			
		}

		outFile.close();
	}
}

subscribers CAddressBook::Find(
	const std::string name,
	const std::string address,
	const std::string telephone,
	const std::string email)
{
	subscribers findedSubscribers;
	for(const auto& subscriber : m_subscribers)
	{
		bool isFinded = true;
		if (!name.empty() && !subscriber->FindByName(name))
		{
			isFinded = false;
		}

		if (isFinded && !address.empty() && !subscriber->FindByAddress(address))
		{
			isFinded = false;
		}

		if (isFinded && !telephone.empty() && !subscriber->FindByTelephoneNumber(telephone))
		{
			isFinded = false;
		}

		if (isFinded && !email.empty() && !subscriber->FindByEmail(email))
		{
			isFinded = false;
		}

		if (isFinded)
		{
			findedSubscribers.push_back(subscriber);
		}
	}

	return findedSubscribers;
}

void CAddressBook::DeleteSubscriber(const int index)
{
}

void CAddressBook::UpdateSubscriber(const int index, 
								const std::string name,
								const std::string surname,
								const std::string patronymic,
								const std::string email,
								const std::string telephonNamber,
								const std::string street,
								const std::string house,
								const std::string apartment,
								const std::string city,
								const std::string republic,
								const std::string country)
{
	for (auto& subscriber : m_subscribers)
	{
		if (subscriber->GetIndex() == index)
		{
			m_updateBD = true;

			if (!name.empty())
			{
				subscriber->SetName(name);
			}

			if (!surname.empty())
			{
				subscriber->SetSurname(surname);
			}

			if (!patronymic.empty())
			{
				subscriber->SetPatronymic(patronymic);
			}

			if (!email.empty())
			{
				subscriber->SetEmail(email);
			}

			if (!telephonNamber.empty())
			{
				subscriber->SetTelephoneNumber(telephonNamber);
			}

			if (!street.empty())
			{
				subscriber->SetStreet(street);
			}

			if (!house.empty())
			{
				subscriber->SetHouse(house);
			}

			if (!apartment.empty())
			{
				subscriber->SetApartment(apartment);
			}

			if (!city.empty())
			{
				subscriber->SetCity(city);
			}

			if (!republic.empty())
			{
				subscriber->SetRepublic(republic);
			}

			if (!country.empty())
			{
				subscriber->SetCountry(country);
			}
		}
	}
}

subscribers CAddressBook::GetSubscribers()
{
	return subscribers();
}

string CAddressBook::ReadInputFile(const string fileName)
{
	ifstream inFile(fileName);
	inFile.exceptions(ios::badbit);

	string contentOfInFile((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
	inFile.close();

	return contentOfInFile;
}

void CAddressBook::ParseBaseData(string line, vector<string> &outValues)
{
	boost::regex expression("(?:\\s*(\\w+)\\s*\\[([^\\]]*)\\]\\s*)");
	boost::regex_split(back_inserter(outValues), line, expression);
}
