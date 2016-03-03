#include "stdafx.h"
#include "RulesCalculation.h"
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include <iomanip>
#include <memory>
#include <assert.h>

using namespace std;

static const string RULE = "R";
static const string VALUE = "Q";
static const string PARAM = "S";
static const string PLUS = "+";
static const string MINUS = "-";
static const char SEPARATOR = '|';
static const string NONE = "nan";

typedef map<string, double> Values;

void ReadValuesFromStringToValues(const string& inputString, Values &values)
{
	string item;

	istringstream ss(inputString);
	ss >> std::ws;
	string key;
	while (getline(ss, item, SEPARATOR))
	{
		if (item == RULE)
		{
			break;
		}

		if (item == VALUE)
		{
			continue;
		}

		if (isalpha(item[0]))
		{
			key = item;
		}
		else
		{
			values[key] = stod(item);
		}
	}
}


void Print(const Values& results, ostream& outputStream)
{
	outputStream.setf(ios::fixed);
	outputStream.precision(2);

	for (const auto& value : results)
	{
		outputStream << value.first << " : ";
		
		if (isnan(value.second))
		{
			outputStream << "nan" << endl;
		}
		else
		{
			outputStream << value.second << endl;
		}

	}
}

pair<string, double> CalculateFunctionFromRuleForValuesFromDraft(const vector<string>& rule, Values& draft)
{
	if (rule.size() != 5)
	{
		return{};
	}

	const string& functionName = rule[1];
	const string& operation = rule[2];
	const string& param1 = rule[3];
	const string& param2 = rule[4];

	assert((operation != PLUS) || (operation != MINUS));

	auto iteratorOfParam1 = draft.find(param1);
	auto iteratorOfParam2 = draft.find(param2);
	if ((iteratorOfParam1 == draft.end()) 
		|| (iteratorOfParam2 == draft.end()) 
		|| isnan(iteratorOfParam1->second) 
		|| isnan(iteratorOfParam2->second))
	{
		draft[functionName] = NAN;
	}
	else
	{
		double resultOfOperation;
		if (operation == PLUS)
		{
			resultOfOperation = iteratorOfParam1->second + iteratorOfParam2->second;
		}
		else if (operation == MINUS)
		{
			resultOfOperation = iteratorOfParam1->second - iteratorOfParam2->second;
		}

		draft[functionName] = resultOfOperation;
	}

	return{ functionName, draft[functionName] };
}

double GetValueForParam(const string& param, const Values& values)
{
	auto it = values.find(param);
	return (it != values.end()) ? it->second : NAN;
}

void CalculationByRulesFromInputToOutputStream(istream& inputStream, ostream& outputStream)
{
	Values values;
	Values results;
	Values draft;
	vector<string>rules;

	vector<string> quote;
	string line, item;

	while (getline(inputStream, line))
	{
		if (!line.empty())
		{
			istringstream ss(line);
			getline(ss, item, SEPARATOR);
			if (item == VALUE)
			{
				ReadValuesFromStringToValues(line, values);
			}
			else if (item == RULE)
			{
				rules.push_back(line);
			}
		}
	}

	for (const string& rule : rules)
	{
		quote.clear();
		istringstream ss(rule);
		while (getline(ss, item, SEPARATOR))
		{
			quote.push_back(item);
		}

		if (quote.size() >= 2)
		{
			if (quote[2] == PARAM)
			{
				draft[quote[1]] = GetValueForParam(quote[1], values);
			}
			else 
			{
				auto pairResult = CalculateFunctionFromRuleForValuesFromDraft(quote, draft);
				if (!pairResult.first.empty())
				{
					results[pairResult.first] = pairResult.second;
				}
			}
		}
	}

	Print(results, outputStream);
}
