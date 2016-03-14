// AddressBook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AddressBook.h"
#include <fstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>

using namespace std;

static const string DATA_BASE = "DataBase.txt";

static const int COLUMN = 10;

static const string NAME = "имя";
static const string SURNAME = "фамилия";
static const string PATRONYMIC = "отчество";
static const string EMAIL = "email";
static const string TELEPHONE_NUMBER = "телефон";
static const string STREET = "улица";
static const string HOUSE = "дом";
static const string APARTMENT = "квартира";
static const string CITY = "город";

CAddressBook::CAddressBook(const string& dataBaseFile)
{
	LoadSubscribersFromDataBaseFile(dataBaseFile);
}

CAddressBook::CAddressBook()
{
	LoadSubscribersFromDataBaseFile(DATA_BASE);
}

void CAddressBook::LoadSubscribersFromDataBaseFile(const string &dataBaseFile)
{
	if (!boost::filesystem::exists(dataBaseFile))
	{
		throw exception("File of data base not exist");
	}

	m_updateBD = false;
	m_dataBase = dataBaseFile;

	m_subscribers.clear();

	ifstream inFile(m_dataBase);
	inFile.exceptions(ios::badbit);

	string lineContentBD;
	while (getline(inFile, lineContentBD))
	{
		auto subscriber = make_shared<CSubscriber>();
		vector<string> values = ParseDataBase(lineContentBD);
		for (size_t i = 0; i < values.size(); i++)
		{
			typedef void (CSubscriber::*StringPropertySetter)(const string& value);

			auto SetSubscriberPropertyForKey = [&](const string& key, StringPropertySetter setter){

				if (values.at(i) == key)
				{
					((*subscriber).*setter)(values.at(++i));
					++i;
				}
			};

			SetSubscriberPropertyForKey(NAME, &CSubscriber::SetName);
			SetSubscriberPropertyForKey(SURNAME, &CSubscriber::SetSurname);
			SetSubscriberPropertyForKey(PATRONYMIC, &CSubscriber::SetPatronymic);
			SetSubscriberPropertyForKey(EMAIL, &CSubscriber::SetEmail);
			SetSubscriberPropertyForKey(TELEPHONE_NUMBER, &CSubscriber::SetTelephoneNumber);
			SetSubscriberPropertyForKey(STREET, &CSubscriber::SetStreet);
			SetSubscriberPropertyForKey(HOUSE, &CSubscriber::SetHouse);
			SetSubscriberPropertyForKey(APARTMENT, &CSubscriber::SetApartment);
			SetSubscriberPropertyForKey(CITY, &CSubscriber::SetCity);
		}

		m_subscribers.push_back(move(subscriber));
	}
}

void CAddressBook::SaveSubscribers()
{
	if (!m_updateBD)
	{
		return;
	}

	ofstream outFile(m_dataBase);
	outFile.exceptions(ios::badbit);

	for (const auto& subscriber : m_subscribers)
	{
		string str;
		AppendProperty(str, NAME, subscriber->GetName());
		AppendProperty(str, SURNAME, subscriber->GetSurname());
		AppendProperty(str, PATRONYMIC, subscriber->GetPatronymic());
		AppendProperty(str, EMAIL, subscriber->GetEmail());
		AppendProperty(str, TELEPHONE_NUMBER, subscriber->GetTelephoneNumber());
		AppendProperty(str, STREET, subscriber->GetStreet());
		AppendProperty(str, HOUSE, subscriber->GetHouse());
		AppendProperty(str, APARTMENT, subscriber->GetApartment());
		AppendProperty(str, CITY, subscriber->GetCity());

		outFile << str << endl;
	}

	m_updateBD = false;
}

void CAddressBook::AppendProperty(string& str, const string& property, const string& value)
{
	str.append(property + "[" + value + "]");
}

subscribers CAddressBook::FindByName(const std::string& name) const
{
	subscribers foundSubscribers;

	auto it = copy_if(m_subscribers.begin(), m_subscribers.end(), back_inserter(foundSubscribers),
		[&name](const shared_ptr<CSubscriber>& subscriber)
	{
		return subscriber->HasName(name);
	});

	return foundSubscribers;
}

subscribers CAddressBook::FindByAddress(const std::string& address) const
{
	subscribers foundSubscribers;

	auto it = copy_if(m_subscribers.begin(), m_subscribers.end(), back_inserter(foundSubscribers),
		[&address](const shared_ptr<CSubscriber>& subscriber)
	{
		return subscriber->HasAddress(address);
	});

	return foundSubscribers;
}

subscribers CAddressBook::FindByTelephone(const std::string& telephone) const
{
	subscribers foundSubscribers;

	auto it = copy_if(m_subscribers.begin(), m_subscribers.end(), back_inserter(foundSubscribers),
		[&telephone](const shared_ptr<CSubscriber>& subscriber)
	{
		return subscriber->HasPhoneNumber(telephone);
	});

	return foundSubscribers;
}

subscribers CAddressBook::FindByEmail(const std::string& email) const
{
	subscribers foundSubscribers;

	auto it = copy_if(m_subscribers.begin(), m_subscribers.end(), back_inserter(foundSubscribers),
		[&email](const shared_ptr<CSubscriber>& subscriber)
	{
		return subscriber->HasEmail(email);
	});

	return foundSubscribers;
}

subscribers CAddressBook::FindByAllParams(
	const std::string& name,
	const std::string& address,
	const std::string& telephone,
	const std::string& email) const
{
	subscribers foundSubscribers;

	if (name.empty() 
		&& address.empty() 
		&& telephone.empty() 
		&& email.empty())
	{
		return foundSubscribers;
	}

	for(const auto& subscriber : m_subscribers)
	{
		bool isFound = true;
		if (!name.empty() && !subscriber->HasName(name))
		{
			isFound = false;
		}

		if (isFound && !address.empty() && !subscriber->HasAddress(address))
		{
			isFound = false;
		}

		if (isFound && !telephone.empty() && !subscriber->HasPhoneNumber(telephone))
		{
			isFound = false;
		}

		if (isFound && !email.empty() && !subscriber->HasEmail(email))
		{
			isFound = false;
		}

		if (isFound)
		{
			foundSubscribers.push_back(subscriber);
		}
	}

	return foundSubscribers;
}

void CAddressBook::DeleteSubscriber(const int index)
{
	m_subscribers.erase(m_subscribers.begin() + index);
	m_updateBD = true;
}

void CAddressBook::UpdateSubscriber(const int index,
	const std::string& name,
	const std::string& surname,
	const std::string& patronymic,
	const std::string& email,
	const std::string& phoneNumber,
	const std::string& street,
	const std::string& house,
	const std::string& apartment,
	const std::string& city)
{
	auto& subscriber = m_subscribers.at(index);
	ModifySubscriber(
		subscriber,
		name,
		surname,
		patronymic,
		email,
		phoneNumber,
		street,
		house,
		apartment,
		city);
}

bool CAddressBook::AddNewSubscriber(
	const std::string& name,
	const std::string& surname,
	const std::string& patronymic,
	const std::string& email,
	const std::string& phoneNumber,
	const std::string& street,
	const std::string& house,
	const std::string& apartment,
	const std::string& city,
	std::string& error)
{
	int newIndex = m_subscribers.size();
	bool setIndex = false;
	for (size_t i = 0; i < m_subscribers.size(); i++)
	{
		if (m_subscribers[i]->HasEmail(email))
		{
			error = "Такой email уже есть";
			return false;
		}
	}

	auto subscriber = make_shared<CSubscriber>();
	if (ModifySubscriber(
		subscriber,
		name,
		surname,
		patronymic,
		email,
		phoneNumber,
		street,
		house,
		apartment,
		city))
	{
		m_subscribers.push_back(subscriber);
	}
	else
	{
		error = "Данные не обновлены.";
		return false;
	}

	return true;
}

bool CAddressBook::ModifySubscriber(const shared_ptr<CSubscriber>& subscriber,
								const std::string& name,
								const std::string& surname,
								const std::string& patronymic,
								const std::string& email,
								const std::string& phoneNumber,
								const std::string& street,
								const std::string& house,
								const std::string& apartment,
								const std::string& city)
{
	typedef void (CSubscriber::*StringPropertySetter)(const string& value);

	bool subscriberUpdated = false;
	auto UpdateSubscriberProperty = [&](StringPropertySetter setter, const string& value){
		if (!value.empty())
		{
			((*subscriber).*setter)(value);
			m_updateBD = true;
			subscriberUpdated = true;
		}
	};

	UpdateSubscriberProperty(&CSubscriber::SetName, name);
	UpdateSubscriberProperty(&CSubscriber::SetSurname, surname);
	UpdateSubscriberProperty(&CSubscriber::SetPatronymic, patronymic);

	string lowercaseEmail(email);
	boost::algorithm::to_lower(lowercaseEmail);
	UpdateSubscriberProperty(&CSubscriber::SetEmail, lowercaseEmail);
	UpdateSubscriberProperty(&CSubscriber::SetTelephoneNumber, phoneNumber);
	UpdateSubscriberProperty(&CSubscriber::SetStreet, street);
	UpdateSubscriberProperty(&CSubscriber::SetHouse, house);
	UpdateSubscriberProperty(&CSubscriber::SetApartment, apartment);
	UpdateSubscriberProperty(&CSubscriber::SetCity, city);

	return subscriberUpdated;
}

subscribers CAddressBook::GetSubscribers()
{
	return m_subscribers;
}

vector<string> CAddressBook::ParseDataBase(string line)
{
	vector<string> outValues;
	boost::regex expression("(?:\\s*(\\w+)\\s*\\[([^\\]]*)\\]\\s*)");
	boost::regex_split(back_inserter(outValues), line, expression);

	return outValues;
}

bool CAddressBook::Updated() const
{
	return m_updateBD;
}