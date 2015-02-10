// rle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream> 
#include <fstream>
#include <algorithm> 
#include <sstream>
#include <memory>
#include <vector>

using namespace std;

static size_t const kFileSize = 1024 * 1024 * 1024 * 2;

struct packedData
{
	unsigned char counter;
	char symbol;
};

size_t FileSize(istream &inputfile)
{
	inputfile.seekg(0, inputfile.end);
	size_t length = (size_t)inputfile.tellg();
	inputfile.seekg(0, inputfile.beg);

	return length;
}

void Pack(const TCHAR *inFile , const TCHAR *outFile)
{
	ifstream inputFile(inFile, ifstream::binary);
	if (!inputFile)
	{
		throw exception("Input file not found.");
	}

	ofstream outputFile(outFile, ofstream::binary);
	if (!outputFile)
	{
		throw exception("Output file not found.");
	}

	packedData data = {};
	while (!inputFile.eof())
	{
		char ch;
		inputFile.read(&ch, sizeof(char));
		if (inputFile.eof() || ((data.counter != 0 ) && (data.symbol != ch)) || (data.counter == 255))
		{
			outputFile.write(reinterpret_cast<char *>(&data), sizeof(packedData));
			data.counter = 0;
		}

		data.symbol = ch;
		data.counter++;
	}
}

void Unpack(const TCHAR *inFile, const TCHAR *outFile)
{
	ifstream inputFile(inFile, ifstream::binary);
	if (!inputFile)
	{
		throw exception("Input file not found.");
	}

	ofstream outputFile(outFile, ofstream::binary);
	if (!outputFile)
	{
		throw exception("Output file not found.");
	}

	while (!inputFile.eof())
	{
		packedData data = {};
		inputFile.read(reinterpret_cast<char *>(&data), sizeof(packedData));
		
		for (int i = 0; i < data.counter; i++)
			outputFile << data.symbol;
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 4)
	{
		cout << "rle.exe pack/unpack <input file> <output file>";
		return 1;
	}

	try
	{
		if (_tcscmp(argv[1], L"pack") == 0)
		{
			Pack(argv[2], argv[3]);
		}
		else if (_tcscmp(argv[1], L"unpack") == 0)
		{
			Unpack(argv[2], argv[3]);
		}
	}
	catch (exception& e)
	{
		cout << e.what();
		return 1;
	}

	return 0;
}

