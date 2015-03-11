// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define BOOST_TEST_MODULE TestsOfAddressBook

#include <boost\test\included\unit_test.hpp>
#include "..\AddressBook\AddressBook.h"
#include <string>
#include <vector>

using namespace std;

BOOST_AUTO_TEST_SUITE(TestsOfAddressBook)

BOOST_AUTO_TEST_CASE(testInitializeAdreessBook)
{
	CAddressBook ab;

	subscribers subscribes(ab.Find("Карамазов"));
	//BOOST_CHECK(subscribes.size() == 3);
}

BOOST_AUTO_TEST_SUITE_END()
