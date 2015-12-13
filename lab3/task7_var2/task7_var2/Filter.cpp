#include "stdafx.h"
#include "Filter.h"
#include <fstream>
#include <algorithm>
#include <locale>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;

vector<string> ParseWordsToVector(string line)
{
	boost::regex expression("(\\w+)");
	vector<string> values;
	boost::regex_split(back_inserter(values), line, expression);

	return values;
}

vector<string> ReadBadWordsFromFile(const string& fileName)
{
	ifstream inFile(fileName);
	inFile.exceptions(ios::badbit);

	string contentOfInFile((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
	
	vector<string> badWords = ParseWordsToVector(contentOfInFile);

	return badWords;
}

bool MatchesWithTemplateBadWords(const string& searchString ,const string& sourceStr, const vector<string>& badWords, size_t positionSearch)
{
	bool matched = false;

	bool endOfStr = (sourceStr.length() == positionSearch) ? true : false;

	if (positionSearch != sourceStr.length()-1)
		++positionSearch;

	for (const auto& badWord : badWords)
	{
		size_t indexOfPos = badWord.find(searchString);
		if (indexOfPos != string::npos)
		{
			if (!endOfStr)
			{
				string tempNextStr = searchString + sourceStr[positionSearch];
				size_t indexOfPosTmp = badWord.find(tempNextStr);

				if (indexOfPosTmp != string::npos)
				{
					matched = true;
					break;
				}
			}
		}
	}

	return matched;
}

string DeleteSubstring(const string& sourceStr, const vector<string>& badWords)
{
	string resultString, tmpStr;

	for (size_t pos = 0; pos < sourceStr.length(); pos++)
	{
		tmpStr += sourceStr[pos];

		if (MatchesWithTemplateBadWords(tmpStr, sourceStr, badWords, pos))
		{
			continue;
		}

		if (find(badWords.begin(), badWords.end(), tmpStr) == badWords.end())
		{
			resultString += tmpStr;
		}
		else
		{
			bool isWordOfBegStr = (pos > tmpStr.length()) ? !isalnum((unsigned char)sourceStr[pos - tmpStr.length()]) : true;
			if (!isWordOfBegStr || isalnum((unsigned char)sourceStr[pos + 1]))
			{
				resultString += tmpStr;
			}
		}

		tmpStr.clear();
	}

	return resultString;
}

string FilterString(const vector<string>& badWords,const string& inputString)
{
	vector<string> values = ParseWordsToVector(inputString);

	return DeleteSubstring(inputString, badWords);
}
