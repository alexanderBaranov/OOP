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

string DeleteSubstring(string& processStr, const string& delSubStr)
{
	int pos = processStr.find(delSubStr);

	while (pos != string::npos)
	{
		bool isWordOfBegStr = pos ? !isalpha((unsigned char)processStr[pos - 1]) : true;
		if (isWordOfBegStr && !isalpha((unsigned char)processStr[pos + delSubStr.length()]))
		{
			processStr.erase(pos, delSubStr.length());
		}

		pos = processStr.find(delSubStr);
	}

	return processStr;
}

string FilterString(const vector<string>& badWords,const string& inputString)
{
	vector<string> values = ParseWordsToVector(inputString);

	setlocale(0, "");

	string resultString(inputString);
	for (const string& badWord : badWords)
	{
		if (find(values.begin(), values.end(), badWord) != values.end())
		{
			resultString = DeleteSubstring(resultString, badWord);
		}
	};

	return resultString;
}

//string Filter(const string& fileName, const string& inputString)
//{
//	auto badWords = ReadBadWordsFromFile(fileName);
//	return FilterString(badWords, inputString);
//}