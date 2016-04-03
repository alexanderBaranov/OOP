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
	{
		CMyString str;
		BOOST_CHECK_EQUAL(str.GetStringData(), "");
	}
	{
		CMyString str("", 30);
		BOOST_CHECK_EQUAL(str.GetStringData(), "");
		BOOST_CHECK_EQUAL(str.GetLength(), 30);
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

	CMyString str6("cat");
	CMyString str7;
	CMyString str8 = str6 + str7;
	
	BOOST_CHECK_EQUAL(str8.GetStringData(), "cat");

	CMyString str9 = str7 + str6;

	BOOST_CHECK_EQUAL(str9.GetStringData(), "cat");
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

BOOST_AUTO_TEST_CASE(testStringComparison)
{
	CMyString str1("hello");
	BOOST_CHECK(str1 == "hello");
	BOOST_CHECK("hello" == str1);
}

BOOST_AUTO_TEST_CASE(testStringConcatenation)
{
	BOOST_CHECK("hello " + CMyString("world") == CMyString("hello world"));
	BOOST_CHECK("hello " + std::string("world") == std::string("hello world"));
	BOOST_CHECK(CMyString("hello ") + std::string("world") == CMyString("hello world"));
	BOOST_CHECK(CMyString("hello ") + "world" == CMyString("hello world"));
	BOOST_CHECK(std::string("hello ") + CMyString("world") == CMyString("hello world"));

	BOOST_CHECK(CMyString() + CMyString("1") == CMyString("1"));
}

BOOST_AUTO_TEST_CASE(testSubstring)
{
	CMyString str("Hello");
	CMyString fer = str.SubString(0, 6);

	BOOST_CHECK_EQUAL(fer.GetStringData(), "Hello");
	BOOST_CHECK_EQUAL(str.SubString(3, 5).GetStringData(), "lo");
	BOOST_CHECK_EQUAL(str.SubString(10, 5).GetStringData(), "");
}

BOOST_AUTO_TEST_CASE(testIndexedAccess)
{
	CMyString str;
	BOOST_CHECK(str[0] == '\0');
	BOOST_CHECK_THROW(str[1], std::exception);

	CMyString hello("Hello");
	BOOST_CHECK(hello[0] == 'H');
	BOOST_CHECK_EQUAL(hello[5], '\0');
	BOOST_CHECK_THROW(hello[6], std::exception);
}

BOOST_AUTO_TEST_CASE(testStringComparison1)
{
	std::string stdstr("Hello\0World", 11);
	std::string hello("Hello");
	CMyString mystr(stdstr);
	BOOST_CHECK(stdstr == stdstr);
	BOOST_CHECK(mystr == stdstr);
	BOOST_CHECK(!(stdstr == hello));
	BOOST_CHECK(!(mystr == hello));

	BOOST_CHECK(stdstr != hello);
	BOOST_CHECK(mystr != hello);
}

BOOST_AUTO_TEST_CASE(testStringConcatenation2)
{
	std::string stdstr("Hello\0World", 11);
	CMyString mystr(stdstr);
	BOOST_CHECK_EQUAL((stdstr + stdstr).length(), 22u);
	BOOST_CHECK_EQUAL((mystr + mystr).GetLength(), 22u);
}

BOOST_AUTO_TEST_CASE(testStringClear)
{
	CMyString mystr("Hello");
	mystr.Clear();
	BOOST_CHECK_EQUAL(mystr.GetStringData(), "");
}

BOOST_AUTO_TEST_CASE(testAssignEmptyString)
{
	CMyString str1("Hello");
	CMyString str2;
	str1 = str2;

	BOOST_CHECK(str1 == "");
	BOOST_CHECK_EQUAL(str1[0], '\0');
}

BOOST_AUTO_TEST_SUITE_END()