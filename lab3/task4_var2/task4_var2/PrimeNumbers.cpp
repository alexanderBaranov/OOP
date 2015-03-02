#include "stdafx.h"
#include <set>

using namespace std;

static const int kMaxUpperBound = 100000000;

set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound == 1)
	{
		return{};
	}

	if (upperBound > kMaxUpperBound)
	{
		throw exception("upperBound > kMaxUpperBound");
	}

	bool isPrimeNumber;
	set<int> primeNumbers({ 2 });
	for (int number = 2; number < upperBound; number++)
	{
		isPrimeNumber = true;
		if ((number % 2) == 0)
		{ 
			continue;
		}
		
		int sq = (int)sqrt(number);

		for (int i = 3; i <= sq; i++)
		{
			if ((number % i) == 0)
			{ 
				isPrimeNumber = false;
				continue;
			}
		}

		if (isPrimeNumber)
			primeNumbers.insert(number);
	}

	return primeNumbers;
}