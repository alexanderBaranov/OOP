// task1_var8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include "TransformVector.h"

using namespace std;

int _tmain()
{
	istream_iterator<double> start(cin);
	istream_iterator<double> end;
	
	vector<double> numbers(start, end);

	TransformVector(numbers);

	sort(numbers.begin(), numbers.end());

	cout.precision(3);
	ostream_iterator<double> output(cout, " ");
	copy(numbers.begin(), numbers.end(), output);

	return 0;
}

