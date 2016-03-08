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
		throw("File not exist");
	}

	m_updateBD = false;
	m_dataBase = dataBaseFile;

	m_subscribers.clear();

	string contentBD = ReadInputFile(m_dataBase);
	vector<string> values;
	ParseBaseData(contentBD, values);

	for (size_t i = 0; i < values.size(); i++)
	{
		auto subscriber= make_shared<CSubscriber>();

		if (values[i] == NAME)
		{
			subscriber->SetName(values[++i]);
		}
		
		if (values[++i] == SURNAME)
		{
			subscriber->SetSurname(values[++i]);
		}
		
		if (values[++i] == PATRONYMIC)
		{
			subscriber->SetPatronymic(values[++i]);
		}
		
		if (values[++i] == EMAIL)
		{
			subscriber->SetEmail(values[++i]);
		}
		
		if (values[++i] == TELEPHONE_NUMBER)
		{
			subscriber->SetTelephoneNumber(values[++i]);
		}
		
		if (values[++i] == STREET)
		{
			subscriber->SetStreet(values[++i]);
		}
		
		if (values[++i] == HOUSE)
		{
			subscriber->SetHouse(values[++i]);
		}
		
		if (values[++i] == APARTMENT)
		{
			subscriber->SetApartment(values[++i]);
		}
		
		if (values[++i] == CITY)
		{
			subscriber->SetCity(values[++i]);
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
		string str(NAME + "[" + subscriber->GetName() + "],");
		str.append(SURNAME + "[" + subscriber->GetSurname() + "],");
		str.append(PATRONYMIC + "[" + subscriber->GetPatronymic() + "],");
		str.append(EMAIL + "[" + subscriber->GetEmail() + "],");
		str.append(TELEPHONE_NUMBER + "[" + subscriber->GetTelephoneNumber() + "],");
		str.append(STREET + "[" + subscriber->GetStreet() + "],");
		str.append(HOUSE + "[" + subscriber->GetHouse() + "],");
		str.append(APARTMENT + "[" + subscriber->GetApartment() + "],");
		str.append(CITY + "[" + subscriber->GetCity() + "];");

		outFile << str << endl;
	}
}

subscribers CAddressBook::FindByName(const std::string& name) const
{
	subscribers foundSubscribers;

	auto it = copy_if(m_subscribers.begin(), m_subscribers.end(), back_inserter(foundSubscribers),
		[&name](shared_ptr<CSubscriber> subscriber)
	{
		return subscriber->HasName(name);
	});

	return foundSubscribers;
}

subscribers CAddressBook::FindByAddress(const std::string& address) const
{
	subscribers foundSubscribers;

	auto it = copy_if(m_subscribers.begin(), m_subscribers.end(), back_inserter(foundSubscribers),
		[&address](shared_ptr<CSubscriber> subscriber)
	{
		return subscriber->HasAddress(address);
	});

	return foundSubscribers;
}

subscribers CAddressBook::FindByTelephone(const std::string& telephone) const
{
	subscribers foundSubscribers;

	auto it = copy_if(m_subscribers.begin(), m_subscribers.end(), back_inserter(foundSubscribers),
		[&telephone](shared_ptr<CSubscriber> subscriber)
	{
		return subscriber->HasPhoneNumber(telephone);
	});

	return foundSubscribers;
}

subscribers CAddressBook::FindByEmail(const std::string& email) const
{
	subscribers foundSubscribers;

	auto it = copy_if(m_subscribers.begin(), m_subscribers.end(), back_inserter(foundSubscribers),
		[&email](shared_ptr<CSubscriber> subscriber)
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
	const std::string& telephonNamber,
	const std::string& street,
	const std::string& house,
	const std::string& apartment,
	const std::string& city)
{
	auto& subscriber = m_subscribers[index];
	ModifySubscriber(
		subscriber,
		name,
		surname,
		patronymic,
		email,
		telephonNamber,
		street,
		house,
		apartment,
		city);
}

string CAddressBook::NewSubscriber(
	const std::string& name,
	const std::string& surname,
	const std::string& patronymic,
	const std::string& email,
	const std::string& telephonNamber,
	const std::string& street,
	const std::string& house,
	const std::string& apartment,
	const std::string& city)
{
	int newIndex = m_subscribers.size();
	bool setIndex = false;
	for (size_t i = 0; i < m_subscribers.size(); i++)
	{
		if (m_subscribers[i]->HasEmail(email))
		{
			return "Такой email уже есть";
		}
	}

	auto subscriber = make_shared<CSubscriber>();
	if (ModifySubscriber(
		subscriber,
		name,
		surname,
		patronymic,
		email,
		telephonNamber,
		street,
		house,
		apartment,
		city))
	{
		m_subscribers.push_back(subscriber);
	}

	return "";
}

bool CAddressBook::ModifySubscriber(shared_ptr<CSubscriber>& subscriber,
								const std::string& name,
								const std::string& surname,
								const std::string& patronymic,
								const std::string& email,
								const std::string& telephonNamber,
								const std::string& street,
								const std::string& house,
								const std::string& apartment,
								const std::string& city)
{
	bool isModify = false;
	if (!name.empty())
	{
		subscriber->SetName(name);
		isModify = true;
	}

	if (!surname.empty())
	{
		subscriber->SetSurname(surname);
		isModify = true;
	}

	if (!patronymic.empty())
	{
		subscriber->SetPatronymic(patronymic);
		isModify = true;
	}

	if (!email.empty())
	{
		string lowercaseEmail(email);
		boost::algorithm::to_lower(lowercaseEmail);
		subscriber->SetEmail(lowercaseEmail);
		isModify = true;
	}

	if (!telephonNamber.empty())
	{
		subscriber->SetTelephoneNumber(telephonNamber);
		isModify = true;
	}

	if (!street.empty())
	{
		subscriber->SetStreet(street);
		isModify = true;
	}

	if (!house.empty())
	{
		subscriber->SetHouse(house);
		isModify = true;
	}

	if (!apartment.empty())
	{
		subscriber->SetApartment(apartment);
		isModify = true;
	}

	if (!city.empty())
	{
		subscriber->SetCity(city);
		isModify = true;
	}

	if (isModify)
	{
		m_updateBD = true;
	}

	return isModify;
}

subscribers CAddressBook::GetSubscribers()
{
	return m_subscribers;
}

string CAddressBook::ReadInputFile(const string& fileName)
{
	ifstream inFile(fileName);
	inFile.exceptions(ios::badbit);

	string contentOfInFile((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());

	return contentOfInFile;
}

void CAddressBook::ParseBaseData(string line, vector<string> &outValues)
{
	boost::regex expression("(?:\\s*(\\w+)\\s*\\[([^\\]]*)\\]\\s*)");
	boost::regex_split(back_inserter(outValues), line, expression);
}

bool CAddressBook::Updated()
{
	return m_updateBD;
}