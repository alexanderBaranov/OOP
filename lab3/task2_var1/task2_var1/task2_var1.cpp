// task2_var1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "StringOperations.h"

using namespace std;

int _tmain()
{
	cout << "Input string: ";
	string srcString;
	getline(cin, srcString);

	cout << "Output string: " << RemoveExtraSpaces(srcString) << endl;

	return 0;
}

