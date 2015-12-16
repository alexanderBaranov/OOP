#include "stdafx.h"
#include "Filter.h"
#include <fstream>
#include <algorithm>
#include <locale>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;

unordered_set<string> ParseWordsToVector(string line)
{
	boost::regex expression("(\\w+)");
	unordered_set<string>values;
	boost::regex_split(inserter(values, values.begin()), line, expression);

	return values;
}

unordered_set<string> ReadBadWordsFromFile(const string& fileName)
{
	ifstream inFile(fileName);
	inFile.exceptions(ios::badbit);

	string contentOfInFile((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
	
	unordered_set<string> badWords = ParseWordsToVector(contentOfInFile);

	return badWords;
}

bool MatchesWithTemplateBadWords(const string& searchString, const unordered_set<string>& badWords)
{
	auto it = badWords.find(searchString);

	return it != badWords.end();
}

string DeleteSubstring(const string& sourceStr, const unordered_set<string>& badWords)
{
	string resultString, tmpStr;

	string resultWord;
	for (const char& symbol : sourceStr)
	{
		if (isalnum(symbol))
		{
			resultWord += symbol;
		}
		else
		{
			if (!resultWord.empty())
			{
				if (!MatchesWithTemplateBadWords(resultWord, badWords))
				{
					resultString += resultWord;
				}

				resultWord.clear();
			}

			resultString += symbol;
		}
	}

	if (!resultWord.empty() && !MatchesWithTemplateBadWords(resultWord, badWords))
	{
		resultString += resultWord;
	}

	return resultString;
}

string FilterString(const unordered_set<string>& badWords, const string& inputString)
{
	return DeleteSubstring(inputString, badWords);
}
