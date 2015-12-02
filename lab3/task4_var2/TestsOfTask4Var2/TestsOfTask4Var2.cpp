// TestsOfTask4Var2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_TEST_MODULE TestsOfTask1Var8

#include <boost\test\included\unit_test.hpp>
#include "..\task4_var2\PrimeNumbers.h"
#include <set>

using namespace std;

BOOST_AUTO_TEST_SUITE(TestsOfTask1Var8)

BOOST_AUTO_TEST_CASE(test_enumerating_prime_numbers)
{
	BOOST_CHECK(GeneratePrimeNumbersSet(1).empty());
	BOOST_CHECK(GeneratePrimeNumbersSet(2) == set<int>({ 2}));
	BOOST_CHECK(GeneratePrimeNumbersSet(10) == set<int>({ 2, 3, 5, 7 }));
	BOOST_CHECK(GeneratePrimeNumbersSet(158) == set<int>({ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 
														43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 
														101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157 }));
}

BOOST_AUTO_TEST_CASE(test_going_beyond_maximum_value)
{
	BOOST_CHECK_THROW(GeneratePrimeNumbersSet(100000001), exception);
}

BOOST_AUTO_TEST_SUITE_END()