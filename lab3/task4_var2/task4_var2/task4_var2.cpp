// task4_var2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "PrimeNumbers.h"

using namespace std;

int _tmain()
{
	cout << "Input upper bound: ";

	try
	{
		int upperBound;
		cin >> upperBound;

		GeneratePrimeNumbersSet(upperBound);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	return 0;
}

