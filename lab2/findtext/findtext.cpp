// findtext.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream> 
#include <iostream> 
#include <string> 
using namespace std;

bool FindStr(const TCHAR* filePath, const TCHAR* strToFind)
{
	ifstream inputFile(filePath);
	if (inputFile.bad())
	{
		cout << "Can't open file.";
		return false;
	}

	bool isFindText = false;
	int numberOflines = 0; //name
	while (!inputFile.eof())
	{
		numberOflines++;

		string strLine;
		getline(inputFile, strLine);

		if (strLine.length())
		{
			if (strLine.find(strToFind) != string::npos)
			{
				cout << numberOflines << "\n";

				isFindText = true;
			}
		}
	}

	return isFindText;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 3)
	{
		cout << "Please, input file path and string to find. Example:findtext.exe <file path> <string to find>.";
		return 1;
	}

	if (!FindStr(argv[1], argv[2]))
	{
		cout << "Text not found";
		return 1;
	}

	return 0;
}

