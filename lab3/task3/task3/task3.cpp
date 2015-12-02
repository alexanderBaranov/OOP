// task3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "WordCount.h"

using namespace std;

int main()
{
	cout << "Input string. Ctrl+z is close input string.\n";

	mapWords words = CountWords(string(istream_iterator<char>(cin >> noskipws), istream_iterator<char>()));

	for(const auto& pair : words)
	{
		cout << pair.first << " = " << pair.second << endl;
	}

	return 0;
}
