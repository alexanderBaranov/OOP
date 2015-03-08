#include "stdafx.h"
#include "WordCount.h"
#include <sstream>
#include <algorithm>
#include <locale>
#include <boost/algorithm/string.hpp>

using namespace std;

string RemoveOtherSymbolsFromWord(string word)
{
	for (int i = word.length(); i != 0; i--)
	{
		if (isalpha((unsigned char)word[i]))
		{
			word = word.substr(0, i + 1);
			break;
		}
	}

	return word;
}

bool IsNoWord(string word)
{
	return (word.length() == 1) && !isalpha((unsigned char)word[0]);
}

mapWords WordCount(string inputString)
{
	stringstream streamStr;
	streamStr << inputString;

	setlocale(0,"");

	mapWords words;
	string word;
	while (streamStr >> word)
	{
		if (IsNoWord(word))
		{
			continue;
		}

		word = RemoveOtherSymbolsFromWord(word);

		auto it = words.find(word);
		if (it != words.end())
		{
			it->second++;
		}
		else
		{
			words[word] = 1;
		}
	}

	return words;
}
