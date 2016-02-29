// CalculationByRules.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RulesCalculation.h"
#include <iostream>
#include <fstream>

using namespace std;

int _tmain()
{
	try
	{
		CalculationByRulesFromInputToOutputStream(cin, cout);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	return 0;
}
