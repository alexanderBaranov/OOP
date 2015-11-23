#include "stdafx.h"
#include "WordCount.h"
#include <sstream>
#include <algorithm>
#include <locale>
#include <fstream>
#include <boost/algorithm/string.hpp>

using namespace std;

string GetWordFromString(string &inputString)
{
	std::locale loc("");

	string resultWord;
	for (size_t i = 0; i < inputString.length(); i++)
	{
		if (isalnum(inputString[i], loc))
		{
			resultWord += inputString.substr(i, 1);
		}
	}

	return resultWord;
}

bool IsDigit(const string &word)
{
	bool isDigit = true;
	try
	{
		double digit = stod(word);
	}
	catch (...)
	{
		isDigit = false;
	}
	return isDigit;
}

mapWords CountWords(const string& inputString)
{
	stringstream streamStr(inputString);
	streamStr.imbue(locale(""));

	mapWords words;
	string word;
	while (streamStr >> word)
	{
		if (!IsDigit(word))
		{
			word = GetWordFromString(word);
			if (!word.empty())
			{
				++words[word];
			}
		}
	}

	return words;
}

mapWords CountWordsFromFile(const TCHAR* filePath)
{
	ifstream inputFile(filePath);

	if (inputFile.bad())
	{
		return {};
	}

	return CountWords(string(istreambuf_iterator<char>(inputFile), istreambuf_iterator<char>()));
}