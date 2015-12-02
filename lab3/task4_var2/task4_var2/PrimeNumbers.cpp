#include "stdafx.h"
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

static const size_t MAX_UPPER_BOUND = 100000000;

set<int> GeneratePrimeNumbersSet(size_t upperBound)
{
	if (upperBound == 1)
	{
		return{};
	}

	if (upperBound > MAX_UPPER_BOUND)
	{
		throw exception("upperBound > kMaxUpperBound");
	}
	
	vector<bool> numbers(upperBound + 1, true);
	set<int> primeNumbers;

	for (size_t i = 2; i <= upperBound; i++)
	{
		if ((i*i <= upperBound) && numbers[i])
		{
			size_t tempCounter = 0;
			for (size_t j = i * i; j <= upperBound; j = i * i + tempCounter * i)
			{
				tempCounter++;
				numbers[j] = false;
			}
		}

		if (numbers[i])
		{
			primeNumbers.insert(primeNumbers.end(), i);
		}
	}

	return primeNumbers;
}
