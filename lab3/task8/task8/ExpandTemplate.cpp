#include "stdafx.h"
#include "ExpandTemplate.h"

using namespace std;

bool MatchesWithTemplateWords(const boost::string_ref& searchString, const templateParams& tmplParams)
{
	for (const auto& pair : tmplParams)
	{
		boost::string_ref templateString(pair.first);

		auto substrOfTemplateString = templateString.substr(0, searchString.length());
		if (substrOfTemplateString == searchString)
		{
			return true;
		}
	}

	return false;
}

const boost::string_ref GetValueFromTemplateWords(const boost::string_ref& key, const templateParams& tmplParams)
{
	for (const auto& pair : tmplParams)
	{
		if (key == pair.first)
		{
			return pair.second;
		}
	}

	return boost::string_ref();
}

string ExpandTemplate(const string& sourceStr, const templateParams& tmplParams)
{
	string resultString;
	size_t startPosSearch = 0;
	for (size_t curPos = 0; curPos < sourceStr.length(); curPos++)
	{
		size_t lengthOfCaptureCharacters = curPos - startPosSearch + 1;

		boost::string_ref searchStr(&sourceStr[startPosSearch], lengthOfCaptureCharacters);

		if ((curPos != sourceStr.length() - 1)
			&& MatchesWithTemplateWords(boost::string_ref(&sourceStr[startPosSearch], searchStr.length() + 1), tmplParams))
		{
			continue;
		}

		boost::string_ref value = GetValueFromTemplateWords(searchStr, tmplParams);
		if (value.begin())
		{
			resultString.append(value.begin(), value.end());
		}
		else
		{
			resultString.append(searchStr.begin(), searchStr.end());
		}

		startPosSearch = curPos + 1;
	}

	return resultString;
}
