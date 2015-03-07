// task8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ExpandTemplate.h"
#include <assert.h>
#include <iostream>
#include <fstream>
#include <locale>
#include <boost/filesystem.hpp>

using namespace std;

string ReadInputFile(const TCHAR *fileName)
{
	ifstream inFile(fileName);
	inFile.exceptions(ios::badbit);

	string contentOfInFile((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
	inFile.close();

	return contentOfInFile;
}

void WriteToOutputFile(const TCHAR *fileName, string text)
{
	ofstream outFile(fileName);
	outFile.exceptions(ios::badbit);

	outFile << text;

	outFile.close();
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc < 5)
	{
		cout << "Example: expand_template.exe <input-file> <output-file> [<param> <value> [<param> <value> ...]]" << endl;
		return 1;
	}

	if (!boost::filesystem::exists(argv[1]))
	{
		cout << "Can't find file: " << argv[1] << endl;
		return 1;
	}

	templateParams params;
	for (int i = 3; i < argc; i++)
	{
		if (i % 2)
		{
			params[argv[i]] = "";
		}
		else
		{
			params[argv[i - 1]] = argv[i];
		}
	}

	try
	{
		string contentOfFile = ReadInputFile(argv[1]);
		WriteToOutputFile(argv[2], ExpandTemplate(contentOfFile, params));
	}
	catch (exception e)
	{
		cout << e.what();
	}
	return 0;
}

