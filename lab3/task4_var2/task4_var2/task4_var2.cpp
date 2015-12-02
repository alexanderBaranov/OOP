// task4_var2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "PrimeNumbers.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc < 2)
	{
		cout << "Example: task4_var2.exe 100000000";
		return 1;
	}

	try
	{
		size_t upperBound = _tstoi(argv[1]);
		auto primeNumbers = GeneratePrimeNumbersSet(upperBound);
		for (int i : primeNumbers)
		{
			cout << i << " ";
		}
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	return 0;
}

