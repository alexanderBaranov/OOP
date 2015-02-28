#include "stdafx.h"
#include "TransformVector.h"
#include <algorithm>

using namespace std;

void TransformVector(std::vector<double> &numbers)
{
	if (numbers.empty())
	{
		return;
	}

	double positiveSum = 0;
	for_each(numbers.begin(), numbers.end(), [&positiveSum](double number)
	{
		if (number > 0)
		{
			positiveSum += number;
		} 
	});

	for (size_t i = 0; i < numbers.size(); i++)
	{
		if (!(i % 2))
		{
			numbers[i] -= positiveSum;
		}
		else
		{
			numbers[i] *= 2;
		}
	}
}