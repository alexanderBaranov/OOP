#include "stdafx.h"
#include "ExpandTemplate.h"
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/cxx11/any_of.hpp>
#include <boost/range/adaptor/map.hpp>
#include <functional>

using namespace std;
using namespace std::placeholders;
using boost::algorithm::any_of;
using boost::adaptors::map_keys;

bool StartsWith(const string& subject, const boost::string_ref & prefix)
{
	return boost::starts_with(subject, prefix);
}

bool MatchesWithTemplateWords(const boost::string_ref& searchString, const templateParams& tmplParams)
{
	return any_of(tmplParams | map_keys, bind(StartsWith, _1, searchString));
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
