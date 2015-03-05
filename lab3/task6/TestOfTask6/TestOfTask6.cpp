// TestOfTask6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_TEST_MODULE TestOfTask6

#include <boost\test\included\unit_test.hpp>
#include <boost/filesystem.hpp>
#include "..\task6\Dictionary.h"
#include <string>

using namespace std;

static const std::string kFileName = "dictionary.txt";

BOOST_AUTO_TEST_SUITE(TestsOfTask6)

BOOST_AUTO_TEST_CASE(testStringOperations)
{
	boost::filesystem::remove(kFileName);

	dictionary newExp({ { "asd", "dsa" }, { "zxc", "czx" } });
	WriteToDictionaryFile((TCHAR*)kFileName.c_str(), newExp);
	dictionary dict = ReadDictionaryFromFile((TCHAR*)kFileName.c_str());

	BOOST_CHECK(dict == newExp);
	BOOST_CHECK_EQUAL(GetValueFromDictionary(dict, "asd"), "dsa");
	BOOST_CHECK_EQUAL(GetValueFromDictionary(dict, "zxc"), "czx");
	BOOST_CHECK(GetValueFromDictionary(dict, "a").empty());
}

BOOST_AUTO_TEST_SUITE_END()

