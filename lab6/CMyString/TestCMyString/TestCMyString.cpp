// TestCMyString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define BOOST_TEST_MODULE TestsOfCMyString

#include <boost\test\included\unit_test.hpp>

#include "../CMyString/MyString.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(TestsOfCMyString)

BOOST_AUTO_TEST_CASE(testConstructors)
{
	{
		CMyString str("cat");
		const char *data = str.GetStringData();
		BOOST_CHECK_EQUAL(data, "cat");
		BOOST_CHECK_EQUAL(data[str.GetLength()], '\0');
	}
	{
		CMyString str("catdog", 3);
		const char *data = str.GetStringData();
		BOOST_CHECK_EQUAL(data, "cat");
		BOOST_CHECK_EQUAL(data[str.GetLength()], '\0');
	}
	{
		CMyString str("cat", 3);
		const char *data = str.GetStringData();
		BOOST_CHECK_EQUAL(data, "cat");
		BOOST_CHECK_EQUAL(data[str.GetLength()], '\0');
	}
	{
		CMyString str("cat", 10);
		const char *data = str.GetStringData();
		BOOST_CHECK_EQUAL(data, "cat");
		BOOST_CHECK_EQUAL(data[str.GetLength()], '\0');
	}
	
	{
		CMyString str1("catdog");
		CMyString str2 = str1.SubString(0, 3);
		BOOST_CHECK_EQUAL(str2.GetStringData(), "cat");
		BOOST_CHECK_EQUAL(str2[3], '\0');
	}
}

BOOST_AUTO_TEST_CASE(testOperatorPlus)
{
	CMyString str1("cat");
	CMyString str2("dog");
	CMyString str3 = str1 + str2;
	BOOST_CHECK_EQUAL(str3.GetStringData(), "catdog");
	BOOST_CHECK_EQUAL(str3.GetStringData()[str3.GetLength()], '\0');

	string str4("dog");
	str3 = str1 + str4;
	BOOST_CHECK_EQUAL(str3.GetStringData(), "catdog");

	char str5[4] = "dog";
	str3 = str1 + str5;
	BOOST_CHECK_EQUAL(str3.GetStringData(), "catdog");
}

BOOST_AUTO_TEST_CASE(testOperatorSquareBrackets)
{
	CMyString str1("cat");
	str1[0] = 'C';
	BOOST_CHECK_EQUAL(str1.GetStringData(), "Cat");
	BOOST_CHECK_EQUAL(str1[0], 'C');
}

BOOST_AUTO_TEST_CASE(testOperatorEquality)
{
	BOOST_CHECK(CMyString("cat") == CMyString("cat"));
	BOOST_CHECK(CMyString("cat") != CMyString("dog"));
}

BOOST_AUTO_TEST_CASE(testOperatorPlusEqual)
{
	CMyString str1("cat");
	CMyString str2("dog");
	str1 += str2;
	BOOST_CHECK_EQUAL(str1.GetStringData(), "catdog");
	BOOST_CHECK_EQUAL(str1[str1.GetLength()], '\0');
}
BOOST_AUTO_TEST_SUITE_END()