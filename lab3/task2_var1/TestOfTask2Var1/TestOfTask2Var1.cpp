// TestOfTask2Var1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_TEST_MODULE TestsOfTask1Var8

#include <boost\test\included\unit_test.hpp>
#include "..\task2_var1\StringOperations.h"

BOOST_AUTO_TEST_SUITE(TestsOfTask1Var8)

BOOST_AUTO_TEST_CASE(testStringOperations)
{
	BOOST_CHECK_EQUAL(RemoveExtraSpaces(" "), "");
	BOOST_CHECK_EQUAL(RemoveExtraSpaces(" 1"), "1");
	BOOST_CHECK_EQUAL(RemoveExtraSpaces("1        "), "1");
	BOOST_CHECK_EQUAL(RemoveExtraSpaces(" 1 "), "1");
	BOOST_CHECK_EQUAL(RemoveExtraSpaces("     1       "), "1");
	BOOST_CHECK_EQUAL(RemoveExtraSpaces(" 1 2"), "1 2");
	BOOST_CHECK_EQUAL(RemoveExtraSpaces(" 1 2 "), "1 2");
	BOOST_CHECK_EQUAL(RemoveExtraSpaces("    1 2    "), "1 2");
	BOOST_CHECK_EQUAL(RemoveExtraSpaces("    1               2    "), "1 2");
	BOOST_CHECK_EQUAL(RemoveExtraSpaces("    asd    xcvxc       sdda    2    "), "asd xcvxc sdda 2");
}

BOOST_AUTO_TEST_SUITE_END()