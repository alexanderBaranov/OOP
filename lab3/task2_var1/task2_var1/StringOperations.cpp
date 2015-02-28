#include "stdafx.h"
#include <string>

using namespace std;

static const string kSpace = " ";
static const string kEmptyString = "";

std::string RemoveExtraSpaces(std::string const& arg)
{
	string resultStr = arg;

	int pos = resultStr.find_first_of(kSpace);
	while (pos != string::npos)
	{
		int next_pos = resultStr.find_first_not_of(kSpace, pos);
		
		int count = next_pos - pos;

		if ((pos == 0) || (next_pos == string::npos))
		{
			resultStr.replace(pos, count, kEmptyString);
		}
		else
		{
			resultStr.replace(pos, count, kSpace);
		}

		pos = resultStr.find_first_of(kSpace, pos + kSpace.length());
	}

	return resultStr;
}