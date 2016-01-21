#include "stdafx.h"
#include "ExpandTemplate.h"
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

bool MatchesWithTemplateWords(const boost::string_ref searchString, const string& sourceStr, const templateParams& tmplParams, size_t positionSearch)
{
	bool matched = false;

	bool endOfStr = (sourceStr.length() == positionSearch) ? true : false;

	size_t startPosSearch = positionSearch > searchString.length() ? positionSearch - searchString.length() + 1 : positionSearch;

	if (positionSearch != sourceStr.length() - 1)
	{
		++positionSearch;
	}

	boost::string_ref nextSearchString(&sourceStr[startPosSearch], (positionSearch != startPosSearch) ? positionSearch - startPosSearch + 1 : positionSearch + 1);

	if (nextSearchString == searchString)
	{
		return false;
	}

	for (const auto& pair : tmplParams)
	{
		size_t indexOfPos = pair.first.find(searchString.to_string());
		if (indexOfPos == 0)
		{
			if (!endOfStr)
			{
				//string temp = searchString.to_string() + sourceStr[positionSearch];
				size_t indexOfPosTmp = pair.first.find(nextSearchString);

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
	string resultString;
	bool substrExit = false;

	boost::posix_time::ptime startTime, stopTime;

	startTime = boost::posix_time::microsec_clock::local_time();

	size_t startPosSearch = 0;
	for (size_t curPos = 0; curPos < sourceStr.length(); curPos++)
	{
		boost::string_ref searchStr(&sourceStr[startPosSearch], curPos - startPosSearch + 1);

		if (MatchesWithTemplateWords(searchStr, sourceStr, tmplParams, curPos))
		{
			continue;
		}

		auto it = tmplParams.find(searchStr);
		if (it != tmplParams.end())
		{
			resultString += it->second.to_string();
		}
		else
		{
			resultString += searchStr.to_string();
		}

		startPosSearch = curPos + 1;
	}

	stopTime = boost::posix_time::microsec_clock::local_time();

	boost::posix_time::time_duration duration = stopTime - startTime;

	long milisec = duration.total_milliseconds();

	cout << "duration = " << milisec << endl;

	return resultString;
}
