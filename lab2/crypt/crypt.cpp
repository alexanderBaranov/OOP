// crypt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream> 
#include <fstream>
#include <algorithm> 
#include <sstream>
#include <functional>

using namespace std;

static size_t const kMaxFileSize = 1024u * 1024u * 1024u * 2u;

unsigned char SwapBits(unsigned char ch, int t1, int t2)
{
	if ((ch >> t1 ^ ch >> t2) & 1)
		ch ^= 1 << t1 | 1 << t2;
	return ch;
}

unsigned char Crypt(char symbol, int key)
{
	unsigned char ch = symbol ^ key;
	ch = _rotl8(ch, 2);
	ch = SwapBits(ch, 6, 7);
	ch = SwapBits(ch, 0, 1);
	ch = SwapBits(ch, 0, 6);

	return ch;
}

unsigned char Decrypt(char symbol, int key)
{
	unsigned char ch = SwapBits(symbol, 0, 6);
	ch = SwapBits(ch, 0, 1);
	ch = SwapBits(ch, 6, 7);
	ch = _rotr8(ch, 2);
	ch ^= key;

	return ch;
}

size_t FileSize(istream &inputfile)
{
	inputfile.seekg(0, inputfile.end);
	size_t length = (size_t)inputfile.tellg();
	inputfile.seekg(0, inputfile.beg);

	return length;
}

void ProcessFiles(const TCHAR *inFile, const TCHAR *outFile, const TCHAR *key, function<char(char&, int)> cryptoFunc)
{
	ifstream inputFile;
	inputFile.exceptions(ios::badbit);

	inputFile.open(inFile, ifstream::binary);


	size_t size = FileSize(inputFile);
	if (size > kMaxFileSize)
	{
		throw exception("Big file");
	}
	
	ofstream outputFile(outFile, ofstream::binary);
	outputFile.exceptions(ios::badbit);

	int keyCrypt = stoi(key);
	
	char ch;
	while (inputFile.get(ch))
		outputFile << cryptoFunc(ch, keyCrypt);

	outputFile.close();
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 5)
	{
		cout << "crypt.exe crypt/decrypt <input file> <output file> <key>";
		return 1;
	}

	try
	{
		if (_tcscmp(argv[1], L"crypt") == 0)
		{
			ProcessFiles(argv[2], argv[3], argv[4], Crypt);
		}
		else if (_tcscmp(argv[1], L"decrypt") == 0)
		{
			ProcessFiles(argv[2], argv[3], argv[4], Decrypt);
		}
	}
	catch (exception const& e)
	{
		cout << e.what();
		return 1;
	}
	return 0;
}

