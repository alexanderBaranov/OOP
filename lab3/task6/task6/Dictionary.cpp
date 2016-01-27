#include "stdafx.h"
#include "Dictionary.h"
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/optional.hpp>
#include <iostream>

using namespace std;

vector<string> ParseMessageTranslation(string& line)
{
	boost::regex expression("(.+)=(.+)");
	vector<string> values;
	boost::regex_split(back_inserter(values), line, expression);

	return values;
}

dictionary GetDictionaryFromStream(istream& inputStream)
{
	dictionary dict;
	for (string line; getline(inputStream, line);)
	{
		vector<string> values = ParseMessageTranslation(line);
		if (values.size() == 2)
		{
			dict[values[0]] = values[1];
		}
	}

	return dict;
}

dictionary ReadDictionaryFromFile(const TCHAR *fileName)
{
	ifstream inFile(fileName);
	inFile.exceptions(ios::badbit);

	return GetDictionaryFromStream(inFile);
}

void WriteDictionaryToStream(const dictionary& dict, ostream& stream)
{
	for (const auto& pair : dict)
	{
		string key = pair.first;
		boost::algorithm::to_lower(key);

		stream << key << "=" << pair.second << endl;
	}
}

bool WriteToDictionaryFile(const TCHAR *fileName, dictionary& dict)
{
	ofstream outFile(fileName, ios::app);
	outFile.exceptions(ios::badbit);

	WriteDictionaryToStream(dict, outFile);
	return true;
}

string GetValueFromDictionary(const dictionary &dict, string key)
{
	string value;

	boost::algorithm::to_lower(key);

	auto it = dict.find(key);

	return it != dict.end() ? it->second : "";
}