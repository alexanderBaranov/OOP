#include "stdafx.h"
#include "WordCount.h"
#include <sstream>
#include <algorithm>
#include <locale>
#include <boost/algorithm/string.hpp>

using namespace std;

string GetWordFromString(string &inputString)
{
	std::locale loc;
	for (size_t i = inputString.length(); i != 0; i--)
	{
		if (isalnum((unsigned char)inputString[i]))
		{
			inputString = inputString.substr(0, i + 1);
			break;
		}
	}

	return inputString;
}

bool IsNoWord(const string &word)
{
	return (word.length() == 1) && !isalpha((unsigned char)word[0]);
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

mapWords WordCount(const string& inputString)
{
	setlocale(0, "");

	stringstream streamStr(inputString);

	mapWords words;
	string word;
	while (streamStr >> word)
	{
		if (IsNoWord(word) || IsDigit(word))
		{
			continue;
		}

		word = GetWordFromString(word);

		++words[word];
	}

	return words;
}
