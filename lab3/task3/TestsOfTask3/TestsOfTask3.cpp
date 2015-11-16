// TestsOfTask3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_TEST_MODULE TestsOfTask3

#include <boost\test\included\unit_test.hpp>
#include "..\task3\WordCount.h"
#include <map>

using namespace std;

BOOST_AUTO_TEST_SUITE(TestsOfTask3)

BOOST_AUTO_TEST_CASE(testStringOperations)
{	
	BOOST_CHECK(WordCount("a a bbbb ; ; bbbb") == mapWords({ { "a", 2 }, { "bbbb", 2 } }));
	BOOST_CHECK(WordCount("привет a a bbbb ; ; bbbb") == mapWords({ {"привет", 1}, { "a", 2 }, { "bbbb", 2 } }));
	BOOST_CHECK(WordCount("привет;;; a a bbbb ; ; bbbb") == mapWords({ { "привет", 1 }, { "a", 2 }, { "bbbb", 2 } }));
	BOOST_CHECK(WordCount("asd zxc s , , s asd") == mapWords({ { "asd", 2 }, { "zxc", 1 }, { "s", 2 } }));
	BOOST_CHECK(WordCount(" , , , , asd zxc s , , s asd") == mapWords({ { "asd", 2 }, { "zxc", 1 }, { "s", 2 } }));
	BOOST_CHECK(WordCount("R2D2") == mapWords({ { "R2D2", 1 } }));
	BOOST_CHECK(WordCount("7777 это цифра") == mapWords({ { "это", 1 }, {"цифра", 1} }));
}

BOOST_AUTO_TEST_SUITE_END()