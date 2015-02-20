// Solve.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream> 
#include <iostream> 
#include <string>
#include <math.h>
using namespace std;

double Discriminant(double a, double b, double c)
{
	return pow(b, 2) - 4 * a * c;
}

double X1(double a, double b, double c, double discriminant)
{
	return (-b + sqrt(discriminant)) / (2 * a * c);
}

double X2(double a, double b, double c, double discriminant)
{
	return (-b - sqrt(discriminant)) / (2 * a * c);
}

void Roots(double a, double b, double c, double& x1, double& x2)
{
	if (!a)
	{
		throw exception("A = 0 - the equation is not square");
	}

	double discriminant = Discriminant(a, b, c);
	if (discriminant < 0)
	{
		throw exception("D < 0");
	}

	x1 = X1(a, b, c, discriminant);
	x2 = X2(a, b, c, discriminant);
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
		double x1, x2;
		Roots(stod(argv[1]), stod(argv[2]), stod(argv[3]), x1, x2);

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
	catch (const exception& error)
	{
		cout << error.what() << '\n';
		return 1;
	}

	return 0;
}

