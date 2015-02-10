// Solve.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream> 
#include <iostream> 
#include <string>
#include <math.h>
using namespace std;

float X1(float a, float b, float c)
{
	float discriminant = powf(b, 2) - 4 * a * c;
	if (discriminant < 0)
	{
		return 0;
	}

	return (-b + sqrtf(discriminant)) / (2 * a * c);
}

float X2(float a, float b, float c)
{
	float discriminant = powf(b, 2) - 4 * a * c;
	if (discriminant < 0)
	{
		return 0;
	}

	return (-b - sqrtf(discriminant)) / (2 * a * c);
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 4)
	{
		cout << "Example: solve.exe <A> <B> <C>";
		return 1;
	}

	cout.precision(3);

	try
	{
		float a = stof(argv[1]);

		if (!a)
		{
			cout << "A = 0 - the equation is not square";
			return 1;
		}

		float b = stof(argv[2]);
		float c = stof(argv[3]);

		float x1 = X1(a, b, c);
		float x2 = X2(a, b, c);

		if (x1 == x2)
		{
			cout << "x1 = x2 = " << x1;
		}
		else
		{
			cout << "x1 = " << x1 << endl;
			cout << "x2 = " << x2 << endl;
		}
	}
	catch (const invalid_argument& error)
	{
		cout << error.what() << '\n';
		return 1;
	}

	return 0;
}

