#include "stdafx.h"
#include "Filter.h"
#include <fstream>
#include <algorithm>
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


string FilterString(vector<string>& badWords,string inputString)
{
	vector<string> values = GetExpression(inputString);

	for_each(badWords.begin(), badWords.end(), [&inputString, &values](string value)
	{
		if (find(values.begin(), values.end(), value) != values.end())
		{
			int pos = inputString.find_first_of(value);
			while (pos != string::npos)
			{
				inputString.erase(pos, pos + value.length());
				pos = inputString.find_first_of(value, pos + value.length());
			}
		}
	});

	return inputString;
}