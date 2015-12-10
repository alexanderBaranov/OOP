// task7_var2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Filter.h"
#include <iostream> 
#include <string>
#include <atlbase.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 2)
	{
		cout << "Example: task7_var2.exe <input file>";
		return 1;
	}

	setlocale(LC_CTYPE, "");

	try
	{
		USES_CONVERSION;

		auto badWords = ReadBadWordsFromFile(T2A(argv[1]));

		istream_iterator<char>in_it;
		do{
			cout << "Input string(Ctrl+z is close input string. Input only '.' and Ctrl+z exit programm): ";
			cin.clear();

			in_it = cin >> noskipws;
			string inStr(in_it, istream_iterator<char>());

			cout << "Output string: " << FilterString(badWords, inStr) << endl;

		} while (*in_it != '.');
	}
	catch (exception e)
	{
		cout << e.what();
	}

	return 0;
}

