#include "stdafx.h"
#include "Dictionary.h"
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

using namespace std;

vector<string> GetExpression(string line)
{
	boost::regex expression("(.+)=(.+)");
	vector<string> values;
	if (!boost::regex_split(back_inserter(values), line, expression))
	{
		return{};
	}

	return values;
}

dictionary ReadDictionaryFromFile(const TCHAR *fileName)
{
	ifstream inFile(fileName);
	inFile.exceptions(ios::badbit);

	dictionary dict;
	for (string line; getline(inFile, line);)
	{
		vector<string> values = GetExpression(line);
		if (values.size())
		{
			dict[values[0]] = values[1];
		}
	}

	inFile.close();

	return dict;
}

bool WriteToDictionaryFile(const TCHAR *fileName, dictionary dict)
{
	ofstream outFile(fileName, ios::app);
	outFile.exceptions(ios::badbit);

	for (const auto& pair : dict)
	{
		string key = pair.first;
		boost::algorithm::to_lower(key);

		outFile << key << "=" << pair.second << endl;
	}

	outFile.close();

	return true;
}

string GetValueFromDictionary(dictionary &dict, string key)
{
	string value;

	boost::algorithm::to_lower(key);

	auto it = dict.find(key);

	return it != dict.end() ? it->second : "";
}