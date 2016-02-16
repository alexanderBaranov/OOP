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

map<string, string> ReadValuesFromStream(istream& inputStream)
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

void CalculationByRulesFromInputToOutputStream(istream& inputStream, ostream& outputStream)
{
	map<string, string> values = ReadValuesFromStream(inputStream);
	Values result;
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
					string value = values[quote[1]];
					draft[quote[1]] = !value.empty() ? value : "nan";
				}
				else if (quote[2] == "+")
				{
					if ((draft[quote[3]] == "nan") || (draft[quote[4]] == "nan") || draft[quote[3]].empty())
					{
						draft[quote[1]] = "nan";
						result[quote[1]] = "nan";
					}
					else
					{
						draft[quote[1]] = to_string(stod(draft[quote[3]]) + stod(draft[quote[4]]));
						result[quote[1]] = draft[quote[1]];
					}
				}
				else if (quote[2] == "-")
				{
					if ((draft[quote[3]] == "nan") || (draft[quote[4]] == "nan") || draft[quote[3]].empty())
					{
						draft[quote[1]] = "nan";
						result[quote[1]] = "nan";
					}
					else
					{
						draft[quote[1]] = to_string(stod(draft[quote[3]]) - stod(draft[quote[4]]));
						result[quote[1]] = draft[quote[1]];
					}
				}
			}
		}
	}

	Print(result, outputStream);
}
