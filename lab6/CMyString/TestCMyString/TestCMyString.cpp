// TestCMyString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define BOOST_TEST_MODULE TestsOfCMyString

#include <boost\test\included\unit_test.hpp>

#include "../CMyString/MyString.h"

using namespace std;

template <size_t N>
void ExpectZeroTerminatedStringData(CMyString const& s, const char(&data)[N])
{
	static_assert(N > 0, "Non-zero array is expected");
	BOOST_REQUIRE_EQUAL(s[N - 1], '\0');
	BOOST_REQUIRE_EQUAL(s.GetLength(), N - 1);
	BOOST_REQUIRE_EQUAL(memcmp(s.GetStringData(), data, N), 0u);
	BOOST_REQUIRE_EQUAL(s.GetStringData()[s.GetLength()], '\0');
}

BOOST_AUTO_TEST_SUITE(TestsOfCMyString)

BOOST_AUTO_TEST_CASE(testConstructors)
{
	ExpectZeroTerminatedStringData(CMyString("cat"), "cat");
	ExpectZeroTerminatedStringData(CMyString("catdog", 3), "cat");
	ExpectZeroTerminatedStringData(CMyString("cat", 3), "cat");	
	ExpectZeroTerminatedStringData(CMyString("cat\0dog\0pie", 10), "cat\0dog\0pi");
	ExpectZeroTerminatedStringData(CMyString(""), "");
	ExpectZeroTerminatedStringData(CMyString("Hello\0", 5), "Hello");

	CMyString str("", 30);
	BOOST_CHECK_EQUAL(str.GetStringData(), "");
	BOOST_CHECK_EQUAL(str.GetLength(), 30);
}

BOOST_AUTO_TEST_CASE(testOperatorPlus)
{
	CMyString str1("cat");
	CMyString str2("dog");
	CMyString str3 = str1 + str2;
	ExpectZeroTerminatedStringData(str3, "catdog");

	char str4[4] = "dog";
	str3 = str1 + str4;
	ExpectZeroTerminatedStringData(str3, "catdog");

	CMyString str6("cat");
	CMyString str7;
	CMyString str8 = str6 + str7;
	
	ExpectZeroTerminatedStringData(str8, "cat");

	CMyString str9(str7 + str6);
	ExpectZeroTerminatedStringData(str9, "cat");
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
	ExpectZeroTerminatedStringData(str1 += str2, "catdog");
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

	ExpectZeroTerminatedStringData(str.SubString(0, 6), "Hello");
	ExpectZeroTerminatedStringData(str.SubString(3, 5), "lo");
	ExpectZeroTerminatedStringData(str.SubString(10, 5), "");
	ExpectZeroTerminatedStringData(str.SubString(5, 10), "");
	ExpectZeroTerminatedStringData(str.SubString(0, 10), "Hello");
}

BOOST_AUTO_TEST_CASE(testIndexedAccess)
{
	CMyString str;
	BOOST_CHECK(str[0] == '\0');
	BOOST_CHECK_THROW(str[1], std::out_of_range);

	CMyString hello("Hello");
	BOOST_CHECK(hello[0] == 'H');
	BOOST_CHECK_EQUAL(hello[5], '\0');
	BOOST_CHECK_THROW(hello[6], std::out_of_range);
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