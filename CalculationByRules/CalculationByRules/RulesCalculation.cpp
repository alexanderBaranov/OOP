#include "stdafx.h"
#include "RulesCalculation.h"
#include <vector>
#include <sstream>
#include <string>
#include <boost/utility/string_ref.hpp>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace boost;

typedef map<string, string> Values;

Values ReadValuesFromStream(istream& inputStream)
{
	map<string, string> values;
	string line, item;

	while (getline(inputStream, line))
	{
		if (!line.empty())
		{
			istringstream ss(line);
			ss >> std::ws;
			string key;
			while (getline(ss, item, '|'))
			{
				if (item == "R")
				{
					break;
				}

				if (item == "Q")
				{
					continue;
				}

				if (isalpha(item[0]))
				{
					key = item;
				}
				else
				{
					values[key] = item;
				}
			}
		}
	}

	return values;
}

void Print(const Values& results, ostream& outputStream)
{
	vector<pair<string, string>> pairs;
	for (auto& it : results)
	{
		pairs.push_back(it);
	}

	sort(pairs.begin(), pairs.end(), [](pair<string, string> const& a, pair<string, string> const& b)
	{
		return a.first < b.first;
	});

	for (const auto& value : pairs)
	{
		if (isalpha(value.second[0]))
		{
			outputStream << value.first << " : " << value.second << endl;
		}
		else
		{
			outputStream << value.first << " : " << setprecision(4) << stod(value.second) << endl;
		}
	}
}

void CalculatFunction(const vector<string>& quote, Values& draft, Values& results)
{
	const string& functionName = quote[1];
	const string& operation = quote[2];
	const string& param1 = quote[3];
	const string& param2 = quote[4];

	if ((draft[param1] == "nan") || (draft[param2] == "nan") || draft[param1].empty() || draft[param2].empty())
	{
		draft[functionName] = "nan";
	}
	else
	{
		double numberOfParam1 = stod(draft[param1]);
		double numberOfParam2 = stod(draft[param2]);
		if (operation == "+")
		{
			numberOfParam1 += numberOfParam2;
		}
		else if (operation == "-")
		{
			numberOfParam1 -= numberOfParam2;
		}

		draft[functionName] = to_string(numberOfParam1);
	}

	results[functionName] = draft[functionName];
}

string GetValueForParam(const string& param, Values& values)
{
	string value = values[param];
	return !value.empty() ? value : "nan";
}

void CalculationByRulesFromInputToOutputStream(istream& inputStream, ostream& outputStream)
{
	Values values = ReadValuesFromStream(inputStream);
	Values results;
	Values draft;

	inputStream.clear();
	inputStream.seekg(0, inputStream.beg);

	vector<string> quote;
	string line, item;
	while (getline(inputStream, line))
	{
		if (!line.empty())
		{
			quote.clear();
			istringstream ss(line);
			while (getline(ss, item, '|'))
			{
				if (item == "Q")
				{
					break;
				}

				quote.push_back(item);
			}

			if (!quote.empty())
			{
				if (quote[2] == "S")
				{
					draft[quote[1]] = GetValueForParam(quote[1], values);
				}
				else 
				{
					CalculatFunction(quote, draft, results);
				}
			}
		}
	}

	Print(results, outputStream);
}
