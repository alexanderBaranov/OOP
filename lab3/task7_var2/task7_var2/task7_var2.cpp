// task7_var2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Filter.h"
#include <iostream> 
#include <string>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 2)
	{
		cout << "Example: task7_var2.exe <input file>";
		return 1;
	}

	setlocale(LC_CTYPE, "");

	cout << "Input string: ";

	try
	{
		string inStr;
		getline(cin, inStr);

		cout << "Output string: " << Filter(argv[1], inStr) << endl;
	}
	catch (exception e)
	{
		cout << e.what();
	}

	return 0;
}

