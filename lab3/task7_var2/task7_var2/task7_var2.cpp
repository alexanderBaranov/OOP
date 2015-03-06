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
		cout << "Example: task6.exe <input file>";
		return 1;
	}

	setlocale(LC_CTYPE, "");

	try
	{
		auto badWords = ReadBadWordsFromFile(argv[1]);

		string inStr;
		getline(cin, inStr);

		inStr = FilterString(badWords, inStr);
	}
	catch (exception e)
	{
		cout << e.what();
	}

	return 0;
}

