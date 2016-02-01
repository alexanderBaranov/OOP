//// fill.cpp : Defines the entry point for the console application.
////
//
#include "stdafx.h"
#include <fstream> 
#include <iostream> 
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <boost/functional/hash.hpp>

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

template <>
struct hash<Point>
{
	typedef Point      argument_type;
	typedef std::size_t  result_type;

	result_type operator()(const Point & t) const
	{
		std::size_t val{ 0 };
		boost::hash_combine(val, t.x);
		boost::hash_combine(val, t.y);
		return val;
	}
};

void FillObjectFromPoint(const Point& point, vector<string>& sourceFile)
{
	std::unordered_set<Point>pointsToBePainted = {point};
	while (pointsToBePainted.size())
	{
		auto curPoint = pointsToBePainted.begin();
		char& contentsOfPoint = sourceFile[curPoint->y][curPoint->x];

		if (contentsOfPoint == SPACE)
		{
			contentsOfPoint = POINT;
		}

		Point newPoint = { curPoint->x, curPoint->y };
		newPoint.y = (newPoint.y < sourceFile.size() - 1) ? newPoint.y + 1 : newPoint.y;

		if (sourceFile[newPoint.y][newPoint.x] == SPACE)
		{
			pointsToBePainted.insert({ newPoint.x, newPoint.y });
		}
		
		newPoint = { curPoint->x, curPoint->y };
		newPoint.y = (newPoint.y != 0) ? newPoint.y - 1 : newPoint.y;

		if (sourceFile[newPoint.y][newPoint.x] == SPACE)
		{
			pointsToBePainted.insert({ newPoint.x, newPoint.y });
		}
		
		newPoint = { curPoint->x, curPoint->y };
		newPoint.x = (newPoint.x < sourceFile[newPoint.y].length() - 1) ? newPoint.x + 1 : newPoint.x;

		if (sourceFile[newPoint.y][newPoint.x] == SPACE)
		{
			pointsToBePainted.insert({ newPoint.x, newPoint.y });
		}
		
		newPoint = { curPoint->x, curPoint->y };
		newPoint.x = (newPoint.x != 0) ? newPoint.x - 1 : newPoint.x;

		if (sourceFile[newPoint.y][newPoint.x] == SPACE)
		{
			pointsToBePainted.insert({ newPoint.x, newPoint.y });
		}

		pointsToBePainted.erase(curPoint);
	}
}

void FillObjectsFromPoints(const vector<Point>& pointsMarkersFill, vector<string>& sourceFile)
{
	for (const auto& point : pointsMarkersFill)
	{
		FillObjectFromPoint(point, sourceFile);
	}
}

vector<Point> FindMarkersFill(const vector<string>& sourceFile)
{
	vector<Point> pointsMarkersFill;
	for (size_t i = 0; i < sourceFile.size(); i++)
	{
		const auto& strLine = sourceFile[i];

		int pos = strLine.find_first_of(MARKER_TO_FILL);
		while (pos != string::npos)
		{
			pointsMarkersFill.push_back({ pos, i });
			pos = strLine.find_first_of(MARKER_TO_FILL, pos + 1);
		}
	}

	return pointsMarkersFill;
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
		if (sourceFile.size() >= MAX_SIZE)
		{
			break;
		}

		if (strLine.length() >= MAX_SIZE)
		{
			sourceFile.push_back(strLine.substr(0, MAX_SIZE - 1) + "\n");
		}
		else
		{
			sourceFile.push_back(strLine);
		}
	}

	vector<Point> pointsMarkersFill = FindMarkersFill(sourceFile);

	FillObjectsFromPoints(pointsMarkersFill, sourceFile);

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

