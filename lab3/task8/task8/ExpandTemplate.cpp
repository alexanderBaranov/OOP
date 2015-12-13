#include "stdafx.h"
#include "ExpandTemplate.h"

using namespace std;

bool MatchesWithTemplateBadWords(const string& searchString, const string& sourceStr, const templateParams& tmplParams, size_t positionSearch)
{
	bool matched = false;

	bool endOfStr = (sourceStr.length() == positionSearch) ? true : false;

	if (positionSearch != sourceStr.length()-1)
		++positionSearch;

	for (const auto& pair : tmplParams)
	{
		size_t indexOfPos = pair.first.find(searchString);
		if (indexOfPos != string::npos)
		{
			if (!endOfStr)
			{
				string tempNextStr = searchString + sourceStr[positionSearch];
				size_t indexOfPosTmp = pair.first.find(tempNextStr);

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


string ExpandTemplate(const string& sourceStr, const templateParams& tmplParams)
{
	string resultString, tmpStr;
	bool substrExit = false;

	bool exit = false;
	for (size_t pos = 0; pos < sourceStr.length(); pos++)
	{
		bool endOfStr = (sourceStr.length() - 1 == pos) ? true : false;

		tmpStr += sourceStr[pos];

		if (MatchesWithTemplateBadWords(tmpStr, sourceStr, tmplParams, pos))
		{
			exit = false;
			continue;
		}

		auto it = tmplParams.find(tmpStr);
		if (it != tmplParams.end())
		{
			resultString += it->second;
		}
		else
		{
			resultString += tmpStr;
		}

		tmpStr.clear();
	}

	return resultString;
}
