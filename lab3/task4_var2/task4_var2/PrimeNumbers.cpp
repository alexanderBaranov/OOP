#include "stdafx.h"
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

static const size_t kMaxUpperBound = 100000000;

set<int> GeneratePrimeNumbersSet(size_t upperBound)
{
	if (upperBound == 1)
	{
		return{};
	}

	if (upperBound > kMaxUpperBound)
	{
		throw exception("upperBound > kMaxUpperBound");
	}
	
	upperBound++;
	vector<bool> numbers(upperBound, true);
	set<int> primeNumbers;
	for (size_t i = 2; i < upperBound; i++)
	{
		if ((i*i <= upperBound) && numbers[i])
		{
			size_t tempCounter = 0;
			for (size_t j = i*i; j < upperBound; j = i*i + tempCounter * i)
			{
				tempCounter++;
				numbers[j] = false;
			}
		}

		if (numbers[i])
		{
			primeNumbers.insert(i);
		}
	}

	return primeNumbers;
}