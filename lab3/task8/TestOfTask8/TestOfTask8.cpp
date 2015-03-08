// TestOfTask8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_TEST_MODULE TestOfTask7Var2

#include <boost\test\included\unit_test.hpp>
#include "..\task8\ExpandTemplate.h"
#include <string>
#include <vector>

using namespace std;

BOOST_AUTO_TEST_SUITE(TestOfTask7Var2)

BOOST_AUTO_TEST_CASE(testStringOperations)
{
	{
		templateParams params({ { "%USER_NAME%", "Ivan Petrov" }, { "{WEEK_DAY}", "Friday" } });
		BOOST_CHECK_EQUAL(
			ExpandTemplate("Hello, %USER_NAME%. Today is {WEEK_DAY}.", params),
			"Hello, Ivan Petrov. Today is Friday.");
	}

	{
		templateParams params({ { "%USER_NAME%", "Super %USER_NAME% {WEEK_DAY}" }, { "{WEEK_DAY}", "Friday. {WEEK_DAY}" } });
		BOOST_CHECK_EQUAL(
			ExpandTemplate("Hello, %USER_NAME%. Today is {WEEK_DAY}.", params),
			"Hello, Super %USER_NAME% {WEEK_DAY}. Today is Friday. {WEEK_DAY}.");
	}

	{
		string const tpl = "-AABBCCCCCABC+";
		templateParams params;
		params["A"] = "[a]";
		params["AA"] = "[aa]";
		params["B"] = "[b]";
		params["BB"] = "[bb]";
		params["C"] = "[c]";
		params["CC"] = "[cc]";
		BOOST_CHECK(ExpandTemplate(tpl, params) ==
			"-[aa][bb][cc][cc][c][a][b][c]+");
	}
}
BOOST_AUTO_TEST_SUITE_END()
