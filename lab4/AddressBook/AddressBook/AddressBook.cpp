// AddressBook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AddressBook.h"
#include <fstream>
#include <algorithm>
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

CAddressBook::CAddressBook()
{
	LoadSubscribers();
	m_updateBD = false;
}

CAddressBook::~CAddressBook()
{
	//if (m_updateBD)
	//{
	//	SaveSubscribers();
	//}
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

		m_subscribers.push_back(move(subscriber));

		sort(m_subscribers.begin(), m_subscribers.end(), [](shared_ptr<CSubscriber> subscriber1, shared_ptr<CSubscriber> subscriber2){
			return subscriber1->GetIndex() < subscriber2->GetIndex();
		});
	}
}

void CAddressBook::SaveSubscribers()
{
	if (!m_updateBD)
	{
		return;
	}

	ofstream outFile(kBaseData);
	outFile.exceptions(ios::badbit);

	for (const auto& subscriber : m_subscribers)
	{
		string str(kIndex + "[" + to_string(subscriber->GetIndex()) + "],");
		str.append(kName + "[" + subscriber->GetName() + "],");
		str.append(kSurname + "[" + subscriber->GetSurname() + "],");
		str.append(kPatronymic + "[" + subscriber->GetPatronymic() + "],");
		str.append(kEmail + "[" + subscriber->GetEmail() + "],");
		str.append(kTelephoneNumber + "[" + subscriber->GetTelephoneNumber() + "],");
		str.append(kStreet + "[" + subscriber->GetStreet() + "],");
		str.append(kHouse + "[" + subscriber->GetHouse() + "],");
		str.append(kApartment + "[" + subscriber->GetApartment() + "],");
		str.append(kCity + "[" + subscriber->GetCity() + "];");

		outFile << str << endl;
	}

	outFile.close();
}

subscribers const CAddressBook::FindByName(const std::string name) const
{
	subscribers findedSubscribers;
	for_each(m_subscribers.begin(), m_subscribers.end(), 
		[&findedSubscribers, &name](shared_ptr<CSubscriber> subscriber)
	{
		if (subscriber->FindByName(name))
		{
			findedSubscribers.push_back(subscriber);
		}
	});

	return findedSubscribers;
}

subscribers const CAddressBook::FindByAddress(const std::string address) const
{
	subscribers findedSubscribers;
	for_each(m_subscribers.begin(), m_subscribers.end(),
		[&findedSubscribers, &address](shared_ptr<CSubscriber> subscriber)
	{
		if (subscriber->FindByAddress(address))
		{
			findedSubscribers.push_back(subscriber);
		}
	});

	return findedSubscribers;
}

subscribers const CAddressBook::FindByTelephone(const std::string telephone) const
{
	subscribers findedSubscribers;
	for_each(m_subscribers.begin(), m_subscribers.end(),
		[&findedSubscribers, &telephone](shared_ptr<CSubscriber> subscriber)
	{
		if (subscriber->FindByTelephoneNumber(telephone))
		{
			findedSubscribers.push_back(subscriber);
		}
	});

	return findedSubscribers;
}

subscribers const CAddressBook::FindByEmail(const std::string email) const
{
	subscribers findedSubscribers;
	for_each(m_subscribers.begin(), m_subscribers.end(),
		[&findedSubscribers, &email](shared_ptr<CSubscriber> subscriber)
	{
		if (subscriber->FindByEmail(email))
		{
			findedSubscribers.push_back(subscriber);
		}
	});

	return findedSubscribers;
}

subscribers const CAddressBook::FindByAllParams(
	const std::string name,
	const std::string address,
	const std::string telephone,
	const std::string email) const
{
	subscribers findedSubscribers;

	if (name.empty() 
		&& address.empty() 
		&& telephone.empty() 
		&& email.empty())
	{
		return findedSubscribers;
	}

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
	for (size_t i = 0; i < m_subscribers.size(); i++)
	{
		if (m_subscribers[i]->GetIndex() == index)
		{
			m_subscribers.erase(m_subscribers.begin() + i);
			m_updateBD = true;
			break;
		}
	}
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
	const std::string city)
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
				city);
		}
	}
}

string CAddressBook::NewSubscriber(
	const std::string name,
	const std::string surname,
	const std::string patronymic,
	const std::string email,
	const std::string telephonNamber,
	const std::string street,
	const std::string house,
	const std::string apartment,
	const std::string city)
{
	int newIndex = m_subscribers.size();
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
			return "Такой email уже есть";
		}
	}

	auto subscriber = make_shared<CSubscriber>();
	if (ModifySubscriber(
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
		city))
	{
		m_subscribers.push_back(subscriber);
	}

	return "";
}

bool CAddressBook::ModifySubscriber( shared_ptr<CSubscriber>& subscriber,
								const int index, 
								const std::string name,
								const std::string surname,
								const std::string patronymic,
								const std::string email,
								const std::string telephonNamber,
								const std::string street,
								const std::string house,
								const std::string apartment,
								const std::string city)
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
		subscriber->SetEmail(email);
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
		subscriber->SetIndex(to_string(index));
	}

	return isModify;
}

subscribers CAddressBook::GetSubscribers()
{
	return m_subscribers;
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

bool CAddressBook::Updated()
{
	return m_updateBD;
}