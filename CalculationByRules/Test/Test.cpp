// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_TEST_MODULE TestOfTask8

#include <boost\test\included\unit_test.hpp>
#include "..\CalculationByRules\RulesCalculation.h"
#include <string>
#include <vector>

using namespace std;

BOOST_AUTO_TEST_SUITE(TestOfTask8)

BOOST_AUTO_TEST_CASE(testCalclulationByRules)
{
	istringstream inStream("R|CAT|S\n"
							"R|DOG|S\n"
							"R|CAT_PLUS_DOG|+|CAT|DOG\n"
							"R|CAT|S\n"
							"R|DOG|S\n"
							"R|CAT_PLUS_DOG|+|CAT|DOG\n");
	ostringstream outStream;
	outStream.str();

	CalculationByRulesFromInputToOutputStream(inStream, outStream);

	BOOST_CHECK_EQUAL(outStream.str(), "CAT_PLUS_DOG : nan\n");
}

BOOST_AUTO_TEST_CASE(testCalclulationByRules1)
{
	istringstream inStream("R|CAT|S\n"
							"R|DOG|S\n"
							"R|CAT_PLUS_DOG|+|CAT|DOG\n"
							"Q|CAT|17\n");
	ostringstream outStream;
	outStream.str();

	CalculationByRulesFromInputToOutputStream(inStream, outStream);

	BOOST_CHECK_EQUAL(outStream.str(), "CAT_PLUS_DOG : nan\n");
}

BOOST_AUTO_TEST_CASE(testCalclulationByRules2)
{
	istringstream inStream("R|CAT|S\n"
							"R|DOG|S\n"
							"R|CAT_PLUS_DOG|+|CAT|DOG\n"
							"R|CAT_PLUS_DOG2|+|CAT_PLUS_DOG|CAT_PLUS_DOG\n"
							"R|A_CAT_PLUS_DOG3|-|CAT_PLUS_DOG2|CAT\n"
							"Q|CAT|10\n"
							"Q|DOG|5\n");
	ostringstream outStream;
	outStream.str();

	CalculationByRulesFromInputToOutputStream(inStream, outStream);
		
	BOOST_CHECK_EQUAL(outStream.str(), "A_CAT_PLUS_DOG3 : 20\n"
										"CAT_PLUS_DOG : 15\n"
										"CAT_PLUS_DOG2 : 30\n");
}

BOOST_AUTO_TEST_CASE(testCalclulationByRules3)
{
	istringstream inStream("R|GREEN|S\n"
							"R|YELLOW|S\n"
							"R|RED|-|YELLOW|GREEN\n"
							"R|RED_PLUS_GREEN|+|RED|GREEN\n"
							"R|BLACK|S\n"
							"R|BLACK_MINUS_YELLOW|-|BLACK|YELLOW\n"
							"R|BLUE|-|BLACK_MINUS_YELLOW|GREEN\n"
							"R|BLUE_X2|+|BLUE|BLUE\n"
							"R|BLUE_X4|+|BLUE_X2|BLUE_X2\n"
							"R|BLUE_X5|+|BLUE_X4|BLUE\n"
							"R|BLUE_X10|+|BLUE_X5|BLUE_X5\n"
							"Q|BLACK|100\n"
							"Q|YELLOW|70\n"
							"Q|GREEN|20\n"
							"Q|BLACK|200\n"
							"Q|GREEN|80\n");
	ostringstream outStream;
	outStream.str();

	CalculationByRulesFromInputToOutputStream(inStream, outStream);

	BOOST_CHECK_EQUAL(outStream.str(), "BLACK_MINUS_YELLOW : 130\n"
										"BLUE : 50\n"
										"BLUE_X10 : 500\n"
										"BLUE_X2 : 100\n"
										"BLUE_X4 : 200\n"
										"BLUE_X5 : 250\n"
										"RED : -10\n"
										"RED_PLUS_GREEN : 70\n");
}

BOOST_AUTO_TEST_CASE(testCalclulationByRules4)
{
	istringstream inStream("R | CAT | S\n"
		"R|DOG|S\n"
		"R|CAT|S\n"
		"R|CAT_PLUS_DOG|+|CAT|DOG\n"
		"Q|CAT|10.135\n"
		"Q|DOG|5.851\n");
	ostringstream outStream;
	outStream.str();

	CalculationByRulesFromInputToOutputStream(inStream, outStream);

	BOOST_CHECK_EQUAL(outStream.str(), "CAT_PLUS_DOG : 15.99\n");
}

BOOST_AUTO_TEST_SUITE_END()