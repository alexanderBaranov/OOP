// TestOfTask6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_TEST_MODULE TestOfTask6

#include <boost\test\included\unit_test.hpp>
#include <boost/filesystem.hpp>
#include <boost/scope_exit.hpp>
#include "..\task6\Dictionary.h"
#include <string>

using namespace std;

struct Dictinoary
{
	Dictinoary()
	{
		istringstream stream("this=���\ntest=����\nstream=������");
		dict = GetDictionaryFromStream(stream);
	};

	dictionary dict;
};

BOOST_FIXTURE_TEST_SUITE(TestsOfTask6, Dictinoary)

BOOST_AUTO_TEST_CASE(test_get_dictionary_from_stream)
{
	BOOST_CHECK(dict == dictionary({ { "this", "���" }, { "test", "����" }, { "stream", "������" } }));
	
	istringstream stream("");
	dictionary dict2 = GetDictionaryFromStream(stream);

	BOOST_CHECK(dict2.size() == 0);
}

BOOST_AUTO_TEST_CASE(test_write_dictionary_to_stream)
{
	ostringstream stream = GetStreamFromDictionary(dict);

	BOOST_CHECK_EQUAL(stream.str(), "stream=������\ntest=����\nthis=���\n");
}

BOOST_AUTO_TEST_CASE(test_translate_words)
{
	BOOST_CHECK_EQUAL(GetValueFromDictionary(dict, "this"), "���");
	BOOST_CHECK_EQUAL(GetValueFromDictionary(dict, "stream"), "������");
}

BOOST_AUTO_TEST_CASE(test_translate_non_existen_words)
{
	BOOST_CHECK_EQUAL(GetValueFromDictionary(dict, "who"), "");
	BOOST_CHECK_EQUAL(GetValueFromDictionary(dict, "code"), "");
}

BOOST_AUTO_TEST_CASE(test_empty_dictionary)
{
	BOOST_CHECK(GetValueFromDictionary(dictionary(), "a").empty());
	BOOST_CHECK(GetValueFromDictionary(dictionary(), "").empty());
}

BOOST_AUTO_TEST_CASE(test_translate_uppercase_words)
{
	BOOST_CHECK_EQUAL(GetValueFromDictionary(dict, "This"), "���");
	BOOST_CHECK_EQUAL(GetValueFromDictionary(dict, "sTream"), "������");
}

BOOST_AUTO_TEST_SUITE_END()
