#include "stdafx.h"
#include <set>

using namespace std;

static const int kMaxUpperBound = 100000000;

bool IsEvenNumber(int number)
{
	return (number % 2) == 0;
}

bool IsPrimeNumber(int number)
{
	if (IsEvenNumber(number))
	{
		return false;
	}

	int sq = (int)sqrt(number);
	bool isPrimeNumber = true;

	for (int i = 3; i <= sq; i++)
	{
		if ((number % i) == 0)
		{
			isPrimeNumber = false;
			continue;
		}
	}

	return isPrimeNumber;
}

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

	set<int> primeNumbers({ 2 });
	for (int number = 2; number < upperBound; number++)
	{			
		if (IsPrimeNumber(number))
			primeNumbers.insert(number);
	}

	return primeNumbers;
}