#include "stdafx.h"
#include "Filter.h"
#include <fstream>
#include <algorithm>
#include <locale>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;

vector<string> GetExpression(string line)
{
	boost::regex expression("(\\w+)");
	vector<string> values;
	if (!boost::regex_split(back_inserter(values), line, expression))
	{
		return{};
	}

	return values;
}

vector<string> ReadBadWordsFromFile(const TCHAR *fileName)
{
	ifstream inFile(fileName);
	inFile.exceptions(ios::badbit);

	string contentOfInFile((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
	
	vector<string> badWords;
	vector<string> values = GetExpression(contentOfInFile);
	if (values.size())
	{
		badWords.assign(values.begin(), values.end());
	}

	inFile.close();

	return badWords;
}

string DeleteSubstring(string processStr, string delSubStr)
{
	int pos = processStr.find_first_of(delSubStr);
	{
		while (pos != string::npos)
		{
			bool isWordOfBegStr = pos ? !isalpha((unsigned char)processStr[pos - 1]) : true;
			if (isWordOfBegStr && !isalpha((unsigned char)processStr[pos + delSubStr.length()]))
			{
				processStr.erase(pos, delSubStr.length());
			}

			pos = processStr.find_first_of(delSubStr, pos + delSubStr.length());
		}
	}

	return processStr;
}

string FilterString(vector<string>& badWords,string inputString)
{
	vector<string> values = GetExpression(inputString);

	setlocale(0, "");

	for_each(badWords.begin(), badWords.end(), [&inputString, &values](string value)
	{
		if (find(values.begin(), values.end(), value) != values.end())
		{
			inputString = DeleteSubstring(inputString, value);
		}
	});

	return inputString;
}

string Filter(const TCHAR *fileName, string inputString)
{
	auto badWords = ReadBadWordsFromFile(fileName);
	return FilterString(badWords, inputString);
}