// TestOfTask1Var8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_TEST_MODULE TestsOfTask1Var8

#include <boost\test\included\unit_test.hpp>
#include "..\task1_var8\TransformVector.h"

using namespace std;

bool VerifyTransformVector(vector<double> inputNumbers, vector<double> const& expectedNumbers)
{
	TransformVector(inputNumbers);
	return (inputNumbers == expectedNumbers);
}

BOOST_AUTO_TEST_SUITE(TestsOfTask1Var8)

	BOOST_AUTO_TEST_CASE(testContentOfVector)
	{
		BOOST_CHECK(VerifyTransformVector({}, {}));
		BOOST_CHECK(VerifyTransformVector({2}, {0}));
		BOOST_CHECK(VerifyTransformVector({ -1 }, { -1 }));
		BOOST_CHECK(VerifyTransformVector({ 2, -1 }, { 0, -2 }));
		BOOST_CHECK(VerifyTransformVector({ 2, -1, 4 }, { -4, -2, -2 }));
	}

BOOST_AUTO_TEST_SUITE_END()