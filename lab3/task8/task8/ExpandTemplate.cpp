#include "stdafx.h"
#include "ExpandTemplate.h"

using namespace std;

bool MatchesWithTemplateWords(const boost::string_ref& searchString, const templateParams& tmplParams)
{
	boost::string_ref nextSearchString(searchString.begin(), searchString.length() + 1);
	for (const auto& pair : tmplParams)
	{
		boost::string_ref substrOfTemplateString = pair.first.substr(0, searchString.length());
		if (substrOfTemplateString == searchString)
		{
			substrOfTemplateString = pair.first.substr(0, nextSearchString.length());
			if (substrOfTemplateString == nextSearchString)
			{
				return true;
			}
		}
	}

	return false;
}


string ExpandTemplate(const string& sourceStr, const templateParams& tmplParams)
{
	string resultString;
	size_t startPosSearch = 0;
	for (size_t curPos = 0; curPos < sourceStr.length(); curPos++)
	{
		boost::string_ref searchStr(&sourceStr[startPosSearch], curPos - startPosSearch + 1);

		if (MatchesWithTemplateWords(searchStr, tmplParams))
		{
			continue;
		}

		auto it = tmplParams.find(searchStr);
		if (it != tmplParams.end())
		{
			auto templateString = it->second;
			resultString.append(templateString.begin(), templateString.end());
		}
		else
		{
			resultString.append(searchStr.begin(), searchStr.end());
		}

		startPosSearch = curPos + 1;
	}

	return resultString;
}
