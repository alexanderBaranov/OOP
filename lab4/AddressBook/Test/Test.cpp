// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define BOOST_TEST_MODULE TestsOfAddressBook

#include <boost\test\included\unit_test.hpp>
#include "..\AddressBook\AddressBook.h"
#include <string>
#include <vector>

using namespace std;

static const string DATA_BASE = "BaseData.txt";

BOOST_AUTO_TEST_SUITE(TestsOfAddressBook)

BOOST_AUTO_TEST_CASE(testFinderOfAdreessBook)
{
	CAddressBook ab(DATA_BASE);

	BOOST_CHECK_EQUAL(ab.FindByName("").size(), 0);
	BOOST_CHECK_EQUAL(ab.FindByName("Jon").size(), 0);
	BOOST_CHECK_EQUAL(ab.FindByName("���������").size(), 4);
	BOOST_CHECK_EQUAL(ab.FindByName("��������� ����").size(), 2);
	BOOST_CHECK_EQUAL(ab.FindByName("���� ���������").size(), 2);
	BOOST_CHECK_EQUAL(ab.FindByName("��������� ���� ���������").size(), 1);
	BOOST_CHECK_EQUAL(ab.FindByName("���� ��������� ���������").size(), 1);
	BOOST_CHECK_EQUAL(ab.FindByName("��������� ���� ���������").size(), 1);
	BOOST_CHECK_EQUAL(ab.FindByName("��������� ���� ���������").size(), 1);
	BOOST_CHECK_EQUAL(ab.FindByName("���������� ��������-������� ����������").size(), 1);

	BOOST_CHECK_EQUAL(ab.FindByAddress("").size(), 0);
	BOOST_CHECK_EQUAL(ab.FindByAddress("������-���").size(), 5);
	BOOST_CHECK_EQUAL(ab.FindByAddress("����").size(), 0);
	BOOST_CHECK_EQUAL(ab.FindByAddress("������-���, 67").size(), 1);
	BOOST_CHECK_EQUAL(ab.FindByAddress("������-���, 27").size(), 0);
	BOOST_CHECK_EQUAL(ab.FindByAddress("������-���, 56, 23").size(), 2);
	BOOST_CHECK_EQUAL(ab.FindByAddress("������-���, 56, 24").size(), 0);
	BOOST_CHECK_EQUAL(ab.FindByAddress("������-���, 56, 23").size(), 2);
	BOOST_CHECK_EQUAL(ab.FindByAddress("56, 23, ������-���").size(), 2);

	BOOST_CHECK_EQUAL(ab.FindByEmail("").size(), 0);
	BOOST_CHECK_EQUAL(ab.FindByEmail("dostoevskiy@yandex.ru").size(), 1);
	BOOST_CHECK_EQUAL(ab.FindByEmail("gb@mail.ru").size(), 1);
	BOOST_CHECK_EQUAL(ab.FindByEmail("gb22@mail.ru").size(), 0);

	BOOST_CHECK_EQUAL(ab.FindByTelephone("").size(), 0);
	BOOST_CHECK_EQUAL(ab.FindByTelephone("415626").size(), 2);
	BOOST_CHECK_EQUAL(ab.FindByTelephone("89028905678").size(), 2);
	BOOST_CHECK_EQUAL(ab.FindByTelephone("789065").size(), 1);

	//BOOST_CHECK_EQUAL(ab.Find("", ).size())
}

BOOST_AUTO_TEST_CASE(testAddToAdreessBook)
{
	{
		CAddressBook ab(DATA_BASE);
		BOOST_CHECK(ab.NewSubscriber("�������", "", "�������", "d@mail.ru", "123123", "�����������", "1", "2", "����") == "");
		ab.SaveSubscribers();
	}
	{
		CAddressBook ab(DATA_BASE);
		ab.UpdateSubscriber(6, "", "", "", "", "777777", "", "", "", "");
		ab.SaveSubscribers();
	}
	{
		CAddressBook ab(DATA_BASE);
		subscribers subs = ab.FindByName("�������");
		BOOST_CHECK_EQUAL(subs.size(), 1);
		BOOST_CHECK_EQUAL(subs[0]->GetTelephoneNumber(), "777777");
	}
	{
		CAddressBook ab(DATA_BASE);
		subscribers subs = ab.FindByName("�������");
		BOOST_CHECK_EQUAL(subs.size(), 1);

		BOOST_CHECK(ab.NewSubscriber("�������", "", "�������", "d@mail.ru", "123123", "�����������", "1", "2", "����") == "����� email ��� ����");

		ab.DeleteSubscriber(6);

		ab.SaveSubscribers();
	}
	{
		CAddressBook ab(DATA_BASE);
		subscribers subs = ab.FindByName("�������");
		BOOST_CHECK_EQUAL(subs.size(), 0);
		BOOST_CHECK_EQUAL(ab.GetSubscribers().size(), 6);
	}
}

BOOST_AUTO_TEST_SUITE_END()
