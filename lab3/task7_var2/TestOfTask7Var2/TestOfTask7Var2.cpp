// TestOfTask7Var2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_TEST_MODULE TestOfTask7Var2

#include <boost\test\included\unit_test.hpp>
#include "..\task7_var2\Filter.h"
#include <string>
#include <vector>

using namespace std;

BOOST_AUTO_TEST_SUITE(TestOfTask7Var2)

BOOST_AUTO_TEST_CASE(test_filter_bad_words)
{
	auto badWords = ParseWordsToVector("pig,fool,idiot.\n");
	
	BOOST_CHECK(badWords == vector<string>({ "pig", "fool", "idiot"}));
	BOOST_CHECK_EQUAL(FilterString(badWords, "She walks in beauty, like the pig") , "She walks in beauty, like the ");
	BOOST_CHECK_EQUAL(FilterString(badWords, "This woman is a fool, fool and she eats like a pig and she is a fool"), "This woman is a ,  and she eats like a  and she is a ");
	BOOST_CHECK_EQUAL(FilterString(badWords, "He is a pig, fool, idiot"), "He is a , , ");

	badWords = ParseWordsToVector("idiot stupid shit \n fuck");
	BOOST_CHECK_EQUAL(FilterString(badWords, "This is a fucking shit!"), "This is a fucking !");
}

BOOST_AUTO_TEST_CASE(test_empty_input_string)
{
	auto badWords = ParseWordsToVector("pig,fool,idiot.\n");
	BOOST_CHECK(badWords == vector<string>({ "pig", "fool", "idiot" }));

	BOOST_CHECK_EQUAL(FilterString(badWords, ""), "");
}

BOOST_AUTO_TEST_CASE(test_empty_list_of_bad_words)
{
	vector<string> badWords;

	BOOST_CHECK_EQUAL(FilterString(badWords, "She walks in beauty, like the pig"), "She walks in beauty, like the pig");
}

BOOST_AUTO_TEST_CASE(test_empty_list_of_bad_words_and_empty_input_string)
{
	vector<string> badWords;

	BOOST_CHECK_EQUAL(FilterString(badWords, ""), "");
}

BOOST_AUTO_TEST_SUITE_END()

