// fill.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream> 
#include <iostream> 
#include <string>
#include <vector>
#include <algorithm>
#include <boost/range/algorithm/find.hpp>
using namespace std;

static const char CONTOUR = '#';
static const char MARKER_TO_FILL = 'o';
static const char SPACE = ' ';
static const char POINT = '.';
static const int MAX_SIZE = 100;

struct Point
{
	size_t x;
	size_t y;

	bool operator==(const Point &coord) const
	{
		return (x == coord.x) && (y == coord.y);
	}
};

vector<Point> FindContour(
	Point pointOfContour,
	vector<string>& sourceFile);

bool ContourContainsPoint(const Point point, const vector<Point>& contour)
{
	if (!contour.size())
		return false;

	return boost::find(contour, point) != contour.end();
}

bool IsContour(
	const Point point,
	const vector<Point>& contour,
	const vector<string>& sourceFile)
{
	if (ContourContainsPoint(point, contour))
	{
		return false;
	}

	if ((point.y < sourceFile.size())
		&& (point.x <= sourceFile[point.y].length())
		&& (sourceFile[point.y][point.x] == CONTOUR))
	{
		return true;
	}

	return false;
}

bool IsPointOfArea(const Point &point, const vector<Point>& contour)
{
	auto upperBoundOfContour = find_if(contour.begin(), contour.end(), [&point](Point a)
	{
		return (point.x == a.x) && (point.y > a.y);
	});

	if (upperBoundOfContour != contour.end())
	{
		auto lowerBoundOfContour = find_if(contour.begin(), contour.end(), [&point](Point a)
		{
			return (point.x == a.x) && (point.y < a.y);
		});

		if (lowerBoundOfContour != contour.end())
		{
			return true;
		}
	}

	return false;
}

void SetPoint(const vector<Point>& contour, vector<string>& sourceFile, int y, int x1, int x2)
{
	size_t numberOfBoundariesOfInnerContour = 0;
	vector<Point> anotherContour;
	for (; x1 < x2; ++x1)
	{
		Point temp = { x1, y };
		
		if ((sourceFile[y][x1] == CONTOUR) && !ContourContainsPoint(temp, contour))
		{
			if (anotherContour.empty() || !IsPointOfArea(temp, anotherContour))
			{
				anotherContour = FindContour(temp, sourceFile);
				continue;
			}
		}

		if (!anotherContour.empty() && IsPointOfArea(temp, anotherContour))
		{
			continue;
		}

		if (IsPointOfArea(temp, contour) && (sourceFile[y][x1] == SPACE))
		{
			sourceFile[y][x1] = POINT;
		}
	}	
}



void FillAreaOfContour(const vector<Point>& contour, vector<string>& sourceFile)
{
	for (const auto& point1OfRange : contour)
	{
		for (const auto& point2Ofrange : contour)
		{
			bool isRangeOfFill = (point1OfRange.y == point2Ofrange.y) && (point1OfRange.x != point2Ofrange.x);
			if (isRangeOfFill)
			{
				if (point1OfRange.x < point2Ofrange.x)
				{
					SetPoint(contour, sourceFile, point1OfRange.y, point1OfRange.x, point2Ofrange.x);
				}
				else
				{
					SetPoint(contour, sourceFile, point1OfRange.y, point2Ofrange.x, point1OfRange.x);
				}
			}
		}
	}
}


bool FindFillMarkerFromRange(const vector<Point>& contour, vector<string>& sourceFile, int y, int x1, int x2)
{
	size_t numberOfBoundariesOfInnerContour = 0;
	vector<Point> anotherContour;
	for (; x1 < x2; ++x1)
	{
		Point temp = { x1, y };

		if ((sourceFile[y][x1] == CONTOUR) && !ContourContainsPoint(temp, contour))
		{
			if (anotherContour.empty() || !IsPointOfArea(temp, anotherContour))
			{
				anotherContour = FindContour(temp, sourceFile);
				continue;
			}
		}

		if (!anotherContour.empty() && IsPointOfArea(temp, anotherContour))
		{
			continue;
		}

		if (IsPointOfArea(temp, contour) && (sourceFile[y][x1] == MARKER_TO_FILL))
		{
			return true;
		}
	}

	return false;
}

bool FindFillMarkerFromArea(const vector<Point>& contour, vector<string>& sourceFile)
{
	for (const auto& point1OfRange : contour)
	{
		for (const auto& point2Ofrange : contour)
		{
			bool isRangeFromArea = (point1OfRange.y == point2Ofrange.y) && (point1OfRange.x != point2Ofrange.x);
			if (isRangeFromArea)
			{
				bool foundFillMarker;
				if (point1OfRange.x < point2Ofrange.x)
				{
					foundFillMarker = FindFillMarkerFromRange(contour, sourceFile, point1OfRange.y, point1OfRange.x, point2Ofrange.x);
				}
				else
				{
					foundFillMarker = FindFillMarkerFromRange(contour, sourceFile, point1OfRange.y, point2Ofrange.x, point1OfRange.x);
				}

				if (foundFillMarker)
					return true;
			}
		}
	}

	return false;
}


vector<Point> FindContour(
	Point pointOfContour,
	vector<string>& sourceFile)
{
	bool foundPointOfContour = false;
	vector<Point> contour;

	do
	{
		foundPointOfContour = false;

		if (pointOfContour.x != 0)
		{
			if (!foundPointOfContour && IsContour({ pointOfContour.x - 1, pointOfContour.y }, contour, sourceFile))
			{
				pointOfContour = { pointOfContour.x - 1, pointOfContour.y };
				foundPointOfContour = true;
			}
			else if (!foundPointOfContour && IsContour({ pointOfContour.x - 1, pointOfContour.y + 1 }, contour, sourceFile))
			{
				pointOfContour = { pointOfContour.x - 1, pointOfContour.y + 1 };
				foundPointOfContour = true;
			}
		}

		if (pointOfContour.y != 0)
		{
			if (!foundPointOfContour && IsContour({ pointOfContour.x, pointOfContour.y - 1 }, contour, sourceFile))
			{
				pointOfContour = { pointOfContour.x, pointOfContour.y - 1 };
				foundPointOfContour = true;
			}
			else if (!foundPointOfContour && IsContour({ pointOfContour.x + 1, pointOfContour.y - 1 }, contour, sourceFile))
			{
				pointOfContour = { pointOfContour.x + 1, pointOfContour.y - 1 };
				foundPointOfContour = true;
			}
		}

		if ((pointOfContour.x != 0) && (pointOfContour.y != 0))
		{
			if (!foundPointOfContour && IsContour({ pointOfContour.x - 1, pointOfContour.y - 1 }, contour, sourceFile))
			{
				pointOfContour = { pointOfContour.x - 1, pointOfContour.y - 1 };
				foundPointOfContour = true;
			}
		}

		if (!foundPointOfContour && IsContour({ pointOfContour.x + 1, pointOfContour.y }, contour, sourceFile))
		{
			pointOfContour = { pointOfContour.x + 1, pointOfContour.y };
			foundPointOfContour = true;
		}
		else if (!foundPointOfContour && IsContour({ pointOfContour.x, pointOfContour.y + 1 }, contour, sourceFile))
		{
			pointOfContour = { pointOfContour.x, pointOfContour.y + 1 };
			foundPointOfContour = true;
		}
		else if (!foundPointOfContour && IsContour({ pointOfContour.x + 1, pointOfContour.y + 1 }, contour, sourceFile))
		{
			pointOfContour = { pointOfContour.x + 1, pointOfContour.y + 1 };
			foundPointOfContour = true;
		}

		if (foundPointOfContour)
		{
			contour.push_back(pointOfContour);
		}
	} while (foundPointOfContour);

	return contour;
}

void ContourInline(vector<string>& sourceFile, const int& lineNumber)
{
	const string strInline = sourceFile[lineNumber];
	for (size_t i = 0; i < strInline.length(); i++)
	{
		if (strInline[i] == CONTOUR)
		{
			vector<Point> contour = FindContour({ i, lineNumber }, sourceFile);

			if (FindFillMarkerFromArea(contour, sourceFile))
			{
				FillAreaOfContour(contour, sourceFile);
			}
		}
		//if (strInline[i] == MARKER_TO_FILL)
		//{
		//	size_t posOfContur = strInline.find(CONTOUR, i);
		//	if (posOfContur != string::npos)
		//	{
		//		vector<Point> contour = FindContour({ posOfContur, lineNumber }, sourceFile);

		//		FillAreaOfContour(contour, sourceFile);

		//		i = posOfContur;
		//	}
		//}
	}
}

void FindAndFillObjects(vector<string>& sourceFile)
{
	for (size_t i = 0; i < sourceFile.size(); i++)
	{
		ContourInline(sourceFile, i);
	}
}

void Print(vector<string>& sourceFile, const TCHAR *outputFile)
{
	ofstream outFile(outputFile, ofstream::binary);
	if (!outFile)
	{
		throw exception("Can't open file.");
	}

	for each(string strLine in sourceFile)
	{
		outFile << strLine;
	}
}

void Fill(const TCHAR *inputFile, const TCHAR *outputFile)
{
	ifstream inFile(inputFile, ifstream::binary);
	if (!inFile)
	{
		throw exception("Can't open file.");
	}

	vector<string> sourceFile;
	string strLine;
	while (getline(inFile, strLine))
	{
		if (sourceFile.size() > MAX_SIZE)
		{
			break;
		}

		if (strLine.length() > MAX_SIZE)
		{
			sourceFile.push_back(strLine.substr(0, MAX_SIZE - 1) + "\n");
		}
		else
		{
			sourceFile.push_back(strLine);
		}
	}

	FindAndFillObjects(sourceFile);

	Print(sourceFile, outputFile);
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 3)
	{
		cout << "Example: fill.exe <input file> <output file>";
		return 1;
	}

	try
	{
		Fill(argv[1], argv[2]);
	}
	catch (exception e)
	{
		cout << e.what();
	}

	return 0;
}

