// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define BOOST_TEST_MODULE TestsOfAddressBook

#include <boost\test\included\unit_test.hpp>
#include "..\AddressBook\AddressBook.h"
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

static const string DATA_BASE = "DataBase.txt";
static const string DATA_BASE_2 = "DataBase2.txt";

struct AddressBook
{
	AddressBook()
	{
		m_tempFile = temp_directory_path();
		m_tempFile /= unique_path();

		copy_file(DATA_BASE, m_tempFile);

		ab.LoadSubscribersFromDataBaseFile(m_tempFile.string());
	};

	~AddressBook()
	{
		remove(m_tempFile);
	};

	path m_tempFile;
	CAddressBook ab;
};

BOOST_FIXTURE_TEST_SUITE(TestsOfAddressBook, AddressBook)

BOOST_AUTO_TEST_CASE(testFinderOfAdreessBook)
{
	BOOST_CHECK_EQUAL(ab.FindByName("").size(), 0);
	BOOST_CHECK_EQUAL(ab.FindByName("Jon").size(), 0);
	BOOST_CHECK_EQUAL(ab.FindByName("Карамазов").size(), 4);
	BOOST_CHECK_EQUAL(ab.FindByName("Карамазов Иван").size(), 2);
	BOOST_CHECK_EQUAL(ab.FindByName("Иван Карамазов").size(), 2);
	BOOST_CHECK_EQUAL(ab.FindByName("Карамазов Иван Федорович").size(), 1);
	BOOST_CHECK_EQUAL(ab.FindByName("Иван Федорович Карамазов").size(), 1);
	BOOST_CHECK_EQUAL(ab.FindByName("Федорович Иван Карамазов").size(), 1);
	BOOST_CHECK_EQUAL(ab.FindByName("Федорович Иван Карамазов").size(), 1);
	BOOST_CHECK_EQUAL(ab.FindByName("Абдурахман Сулейман-Батыров Аджанкович").size(), 1);

	BOOST_CHECK_EQUAL(ab.FindByAddress("").size(), 0);
	BOOST_CHECK_EQUAL(ab.FindByAddress("Йошкар-Ола").size(), 5);
	BOOST_CHECK_EQUAL(ab.FindByAddress("Кама").size(), 0);
	BOOST_CHECK_EQUAL(ab.FindByAddress("Йошкар-Ола, 67").size(), 1);
	BOOST_CHECK_EQUAL(ab.FindByAddress("Йошкар-Ола, 27").size(), 0);
	BOOST_CHECK_EQUAL(ab.FindByAddress("Йошкар-Ола, 56, 23").size(), 2);
	BOOST_CHECK_EQUAL(ab.FindByAddress("Йошкар-Ола, 56, 24").size(), 0);
	BOOST_CHECK_EQUAL(ab.FindByAddress("Йошкар-Ола, 56, 23").size(), 2);
	BOOST_CHECK_EQUAL(ab.FindByAddress("56, 23, Йошкар-Ола").size(), 2);

	BOOST_CHECK_EQUAL(ab.FindByEmail("").size(), 0);
	BOOST_CHECK_EQUAL(ab.FindByEmail("dostoevskiy@yandex.ru").size(), 1);
	BOOST_CHECK_EQUAL(ab.FindByEmail("gb@mail.ru").size(), 1);
	BOOST_CHECK_EQUAL(ab.FindByEmail("gb22@mail.ru").size(), 0);

	BOOST_CHECK_EQUAL(ab.FindByTelephone("").size(), 0);
	BOOST_CHECK_EQUAL(ab.FindByTelephone("415626").size(), 2);
	BOOST_CHECK_EQUAL(ab.FindByTelephone("89028905678").size(), 2);
	BOOST_CHECK_EQUAL(ab.FindByTelephone("789065").size(), 1);
}

BOOST_AUTO_TEST_CASE(testAddToAdreessBook)
{
	string error;
	BOOST_CHECK(ab.AddNewSubscriber("Добрыня", "", "Никитич", "d@mail.ru", "123123", "Богатырская", "1", "2", "Росы", error));
	BOOST_CHECK(!ab.AddNewSubscriber("", "", "", "", "", "", "", "", "", error));
	ab.SaveSubscribers();

	subscribers subs = ab.FindByName("Добрыня");
	BOOST_CHECK_EQUAL(subs.size(), 1);
}

BOOST_AUTO_TEST_CASE(testUpdateSubscriber)
{
	string error;
	BOOST_CHECK(ab.AddNewSubscriber("Добрыня", "", "Никитич", "d@mail.ru", "123123", "Богатырская", "1", "2", "Росы", error));
	ab.SaveSubscribers();

	ab.UpdateSubscriber(6, "", "", "", "", "777777", "", "", "", "");
	ab.SaveSubscribers();

	subscribers subs = ab.FindByName("Добрыня");
	BOOST_CHECK_EQUAL(subs.size(), 1);
	BOOST_CHECK_EQUAL(subs[0]->GetTelephoneNumber(), "777777");
}

BOOST_AUTO_TEST_CASE(testAddExistingSubscriber)
{
	string error;
	BOOST_CHECK(ab.AddNewSubscriber("Добрыня", "", "Никитич", "d@mail.ru", "123123", "Богатырская", "1", "2", "Росы", error));
	ab.SaveSubscribers();

	subscribers subs = ab.FindByName("Добрыня");
	BOOST_CHECK_EQUAL(subs.size(), 1);

	BOOST_CHECK(!ab.AddNewSubscriber("Добрыня", "", "Никитич", "d@mail.ru", "123123", "Богатырская", "1", "2", "Росы", error));
	BOOST_CHECK_EQUAL(error, "Такой email уже есть");
}

BOOST_AUTO_TEST_CASE(testDeleteSubscriber)
{
	string error;
	BOOST_CHECK(ab.AddNewSubscriber("Добрыня", "", "Никитич", "d@mail.ru", "123123", "Богатырская", "1", "2", "Росы", error));
	ab.SaveSubscribers();

	ab.DeleteSubscriber(6);
	ab.SaveSubscribers();

	subscribers subs = ab.FindByName("Добрыня");
	BOOST_CHECK_EQUAL(subs.size(), 0);
	BOOST_CHECK_EQUAL(ab.GetSubscribers().size(), 6);
}

void CheckSubscriberData(
	const std::shared_ptr<CSubscriber>& subsciber,
	const string& name,
	const string& surname,
	const string& patronymic,
	const string& email,
	const string& phoneNumber,
	const string& street,
	const string& house,
	const string& apartment,
	const string& city)
{
	BOOST_CHECK_EQUAL(subsciber->GetName(), name);
	BOOST_CHECK_EQUAL(subsciber->GetSurname(), surname);
	BOOST_CHECK_EQUAL(subsciber->GetPatronymic(), patronymic);
	BOOST_CHECK_EQUAL(subsciber->GetEmail(), email);
	BOOST_CHECK_EQUAL(subsciber->GetTelephoneNumber(), phoneNumber);
	BOOST_CHECK_EQUAL(subsciber->GetStreet(), street);
	BOOST_CHECK_EQUAL(subsciber->GetHouse(), house);
	BOOST_CHECK_EQUAL(subsciber->GetApartment(), apartment);
	BOOST_CHECK_EQUAL(subsciber->GetCity(), city);
}

BOOST_AUTO_TEST_CASE(testCheckResultsOfParseData)
{
	CAddressBook ab2(DATA_BASE_2);
	
	subscribers subs =  ab2.FindByEmail("email");
	BOOST_CHECK_EQUAL(subs.size(), 1);
	CheckSubscriberData(subs[0], "фамилие", "де бержерак", "email", "email", "", "", "", "", "");

	subs = ab2.FindByEmail("телефон");
	BOOST_CHECK_EQUAL(subs.size(), 1);
	CheckSubscriberData(subs[0], "сергей", "петров", "николаевич", "телефон", "город", "фамилие", "фамилие", "фамилие", "фамилие");
}

BOOST_AUTO_TEST_CASE(testCheckForTheAbsenceOfDataBase)
{
	BOOST_CHECK_THROW(CAddressBook ab2(""), std::exception);
}

BOOST_AUTO_TEST_SUITE_END()
