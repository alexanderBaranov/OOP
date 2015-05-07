// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../university/UniversityProcess.h"
#define BOOST_TEST_MODULE TestsOfUnivercity

#include <boost\test\included\unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(TestsOfUnivercity)

BOOST_AUTO_TEST_CASE(testEmpty)
{
	//CUniversityProcess asd;

	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
