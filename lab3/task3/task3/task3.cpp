// task3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "WordCount.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 2)
	{
		cout << "Please, input file path. Example:task3.exe <file path>";
		return 1;
	}

	mapWords words = CountWordsFromFile(argv[1]);

	for(const auto& pair : words)
	{
		cout << pair.first << " = " << pair.second << endl;
	}

	return 0;
}

