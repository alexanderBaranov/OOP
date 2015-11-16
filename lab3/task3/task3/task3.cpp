// task3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "WordCount.h"

using namespace std;

int _tmain()
{
	cout << "Input string: ";

	string srcString;
	getline(cin, srcString);

	mapWords words = WordCount(srcString);

	for(const auto& pair : words)
	{
		cout << pair.first << " = " << pair.second << endl;
	}

	return 0;
}

