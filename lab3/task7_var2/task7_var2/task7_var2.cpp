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

	cout << "'exit' is close programm." << endl;

	try
	{
		USES_CONVERSION;

		auto badWords = ReadBadWordsFromFile(T2A(argv[1]));

		cout << "Input string: ";

		string inStr;
		while (getline(cin, inStr))
		{
			if (inStr.compare("exit") == 0)
			{
				break;
			}

			cout << "Output string: " << FilterString(badWords, inStr) << endl << endl;

			cout << "Input string: ";
		}
	}
	catch (exception e)
	{
		cout << e.what();
	}

	return 0;
}

