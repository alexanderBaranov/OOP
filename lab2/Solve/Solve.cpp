// Solve.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream> 
#include <iostream> 
#include <string>
#include <math.h>
using namespace std;

double CalculateDiscriminant(double& a, double& b, double& c)
{
	return pow(b, 2) - 4 * a * c;
}

double X1(double& a, double& b, double& c, double& discriminant)
{
	return (-b + sqrt(discriminant)) / (2 * a * c);
}

double X2(double& a, double& b, double& c, double& discriminant)
{
	return (-b - sqrt(discriminant)) / (2 * a * c);
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
		double a = stod(argv[1]);

		if (!a)
		{
			cout << "A = 0 - the equation is not square" << endl;
			return 1;
		}

		double b = stod(argv[2]);
		double c = stod(argv[3]);

		double discriminant = CalculateDiscriminant(a, b, c);
		if (discriminant < 0)
		{
			cout << "No real numbers (D < 0)." << endl;
			return 1;
		}

		double x1 = X1(a, b, c, discriminant);
		double x2 = X2(a, b, c, discriminant);

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

