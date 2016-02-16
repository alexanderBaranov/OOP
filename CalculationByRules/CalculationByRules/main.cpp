// CalculationByRules.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RulesCalculation.h"
#include <iostream>
#include <fstream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc < 3)
	{
		cout << "Example: CalculationByRules.exe <input file> <output file>" << endl;

		return 1;
	}

	try
	{
		ifstream inFile(argv[1]);
		inFile.exceptions(ios::badbit);

		ofstream outFile(argv[2]);
		outFile.exceptions(ios::badbit);

		CalculationByRulesFromInputToOutputStream(inFile, outFile);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	return 0;
}
