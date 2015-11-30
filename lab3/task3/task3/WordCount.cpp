#include "stdafx.h"
#include "WordCount.h"
#include <sstream>
#include <algorithm>
#include <locale>
#include <fstream>
#include <boost/algorithm/string.hpp>

using namespace std;

mapWords CountWords(const string& inputString)
{
	mapWords words;

	std::locale loc("");
	string resultWord;
	for (const char& symbol : inputString)
	{
		char lowerSymbol = tolower(symbol, loc);
		if (isalnum(lowerSymbol, loc))
		{
			resultWord += lowerSymbol;
		}
		else if (!resultWord.empty())
		{
			boost::algorithm::to_lower(resultWord);

			++words[resultWord];
			resultWord.clear();
		}
	}

	if (!resultWord.empty())
	{
		++words[resultWord];
	}

	return words;
}
