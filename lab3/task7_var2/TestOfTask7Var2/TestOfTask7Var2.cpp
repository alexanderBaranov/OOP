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

BOOST_AUTO_TEST_CASE(testStringOperations)
{
	auto badWords = GetExpression("asd,cvb,sdf,zxc,vvxzcsd.\n");
	
	BOOST_CHECK(badWords == vector<string>({ "asd", "cvb", "sdf", "zxc", "vvxzcsd" }));
	BOOST_CHECK_EQUAL(FilterString(badWords, "khkjhxcv zxcpipiwe asd erttwem,b") , "khkjhxcv zxcpipiwe  erttwem,b");
	BOOST_CHECK_EQUAL(FilterString(badWords, "khkjhxcv zxc asd zxcpipiwe asd erttwem,b"), "khkjhxcv   zxcpipiwe  erttwem,b");
	BOOST_CHECK_EQUAL(FilterString(badWords, "asd khkjhxcv zxc asd zxcpipiwe asd erttwem,b"), " khkjhxcv   zxcpipiwe  erttwem,b");
	BOOST_CHECK_EQUAL(FilterString(badWords, "asd, khkjhxcv zxc ,asd zxcpipiwe asd erttwem,b"), ", khkjhxcv  , zxcpipiwe  erttwem,b");
	BOOST_CHECK_EQUAL(FilterString(badWords, "asd, khkjhxcv zxc ,asd zxcpipiwe asd erttwem,b vvxzcsd"), ", khkjhxcv  , zxcpipiwe  erttwem,b ");
}

BOOST_AUTO_TEST_SUITE_END()

