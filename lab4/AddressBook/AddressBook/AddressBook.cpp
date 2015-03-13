// AddressBook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AddressBook.h"
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/format.hpp>

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
	if (m_updateBD)
	{
		SaveSubscribers();
	}
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

		sort(m_subscribers.begin(), m_subscribers.end(), [](shared_ptr<CSubscriber> subscriber1, shared_ptr<CSubscriber> subscriber2){
			return subscriber1->GetIndex() < subscriber2->GetIndex();
		});

		for (const auto& subscriber : m_subscribers)
		{
			string str(kIndex + "[" + to_string(subscriber->GetIndex()) + "],");
			str.append(kName + "[" + subscriber->GetName() + "],");
			str.append(kSurname + "[" + subscriber->GetSurname() + "],");
			str.append(kPatronymic + "[" + subscriber->GetPatronymic() + "],");
			str.append(kEmail + "[" + subscriber->GetEmail() + "],");
			str.append(kTelephoneNumber + "[" + subscriber->GetTelephoneNumber() + "],");
			str.append(kStreet + "[" + subscriber->GetStreet() + "],");
			str.append(kHouse + "[" + subscriber->GetApartment() + "],");
			str.append(kCity + "[" + subscriber->GetCity() + "],");
			str.append(kRepublic + "[" + subscriber->GetRepublic() + "],");
			str.append(kCountry + "[" + subscriber->GetCountry() + "];");

			outFile << str << endl;
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
			ModifySubscriber(
				subscriber,
				index,
				name,
				surname,
				patronymic,
				email,
				telephonNamber,
				street,
				house,
				apartment,
				city,
				republic,
				country);
		}
	}
}

void CAddressBook::NewSubscriber(const int index,
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
	int newIndex = 0;
	bool setIndex = false;
	for (size_t i = 0; i < m_subscribers.size(); i++)
	{
		if (!setIndex && (i != m_subscribers[i]->GetIndex()))
		{
			newIndex = i;
			setIndex = true;
			break;
		}

		if (m_subscribers[i]->FindByEmail(email))
		{
			throw exception("Email set");
		}
	}

	auto subscriber = make_shared<CSubscriber>();
	ModifySubscriber(
		subscriber,
		newIndex,
		name,
		surname,
		patronymic,
		email,
		telephonNamber,
		street,
		house,
		apartment,
		city,
		republic,
		country);

	m_subscribers.push_back(subscriber);
}

void CAddressBook::ModifySubscriber( shared_ptr<CSubscriber>& subscriber,
								const int index, 
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
