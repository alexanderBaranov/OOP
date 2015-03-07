#include "stdafx.h"
#include "ExpandTemplate.h"

using namespace std;

string ExpandTemplate(const string& sourceStr, templateParams& tmplParams)
{
	string resultString, tmpStr;
	bool substrExit = false;

	bool exit = false;
	size_t sourceLength = sourceStr.length() - 1;
	for (size_t range = 0; range < sourceStr.length(); range++)
	{
		bool endOfStr = (sourceLength == range) ? true : false;

		size_t tmpRange = range;
		tmpStr += sourceStr[range];

		if (!endOfStr)
			++tmpRange;

		for each(const auto& pair in tmplParams)
		{
			size_t indexOfPos = pair.first.find(tmpStr);
			if (indexOfPos != string::npos)
			{
				substrExit = true;

				if (!endOfStr)
				{
					string tempNextStr = tmpStr + sourceStr.substr(tmpRange, 1);
					size_t indexOfPosTmp = pair.first.find(tempNextStr);

					if (indexOfPosTmp != string::npos)
					{
						exit = true;
						break;
					}
				}
			}
		}

		if (exit)
		{
			exit = false;
			continue;
		}

		if (substrExit)
		{
			substrExit = false;
			templateParams::iterator it = tmplParams.find(tmpStr);

			if (it != tmplParams.end())
			{
				resultString += it->second;
			}
			else
			{
				resultString += tmpStr;
			}
		}
		else
		{
			resultString += sourceStr[range];
		}

		tmpStr.clear();
	}

	return resultString;
}
