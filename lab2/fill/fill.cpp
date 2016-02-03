//// fill.cpp : Defines the entry point for the console application.
////
//
#include "stdafx.h"
#include <fstream> 
#include <iostream> 
#include <string>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

static const char CONTOUR = '#';
static const char MARKER_TO_FILL = 'o';
static const char SPACE = ' ';
static const char POINT = '.';
static const int MAX_SIZE = 100;

struct Point
{
	unsigned int x;
	unsigned int y;

	bool operator==(const Point &coord) const
	{
		return (x == coord.x) && (y == coord.y);
	}
};

void TryToAddPointToPainting(const Point& point, deque<Point>& pointsToBePainted, const vector<string>& sourceObjectsToPainting)
{
	if ((point.y >= sourceObjectsToPainting.size())
		|| (point.y <= 0)
		|| (point.x >= sourceObjectsToPainting[point.y].length())
		|| (point.x <= 0))
	{
		return;
	}

	if (sourceObjectsToPainting[point.y][point.x] == SPACE)
	{
		pointsToBePainted.push_back({ point.x, point.y });
	}
}

void FillObjectFromPoint(const Point& point, vector<string>& sourceObjectsToPainting)
{
	deque<Point> pointsToBePainted = {point};
	while (!pointsToBePainted.empty())
	{
		const Point& curPoint = pointsToBePainted.front();
		char& contentsOfPoint = sourceObjectsToPainting[curPoint.y][curPoint.x];

		if (contentsOfPoint == SPACE)
		{
			contentsOfPoint = POINT;
		}

		TryToAddPointToPainting({ curPoint.x, curPoint.y + 1 }, pointsToBePainted, sourceObjectsToPainting);
		TryToAddPointToPainting({ curPoint.x, curPoint.y - 1}, pointsToBePainted, sourceObjectsToPainting);
		TryToAddPointToPainting({ curPoint.x + 1, curPoint.y }, pointsToBePainted, sourceObjectsToPainting);
		TryToAddPointToPainting({ curPoint.x - 1, curPoint.y }, pointsToBePainted, sourceObjectsToPainting);

		pointsToBePainted.pop_front();
	}
}

void FillObjectsFromPoints(const vector<Point>& pointsMarkersFill, vector<string>& sourceObjectsToPainting)
{
	for (const auto& point : pointsMarkersFill)
	{
		FillObjectFromPoint(point, sourceObjectsToPainting);
	}
}

vector<Point> FindFillMarkers(const vector<string>& sourceObjectsToPainting)
{
	vector<Point> pointsMarkersFill;
	for (size_t i = 0; i < sourceObjectsToPainting.size(); i++)
	{
		const auto& strLine = sourceObjectsToPainting[i];

		int pos = strLine.find_first_of(MARKER_TO_FILL);
		while (pos != string::npos)
		{
			pointsMarkersFill.push_back({ pos, i });
			pos = strLine.find_first_of(MARKER_TO_FILL, pos + 1);
		}
	}

	return pointsMarkersFill;
}

void Print(vector<string>& sourceObjectsToPainting, const TCHAR *outputFile)
{
	ofstream outFile(outputFile, ofstream::binary);
	if (!outFile)
	{
		throw exception("Can't open file.");
	}

	for each(string strLine in sourceObjectsToPainting)
	{
		outFile << strLine;
	}
}

vector<string> ReadSourceObjectsToPaintingFromFile(const TCHAR *inputFile)
{
	ifstream inFile(inputFile, ifstream::binary);
	if (!inFile)
	{
		throw exception("Can't open file.");
	}

	vector<string> sourceObjectsToPainting;
	string strLine;
	while (getline(inFile, strLine))
	{
		if (sourceObjectsToPainting.size() >= MAX_SIZE)
		{
			break;
		}

		if (strLine.length() >= MAX_SIZE)
		{
			sourceObjectsToPainting.push_back(strLine.substr(0, MAX_SIZE - 1) + "\n");
		}
		else
		{
			sourceObjectsToPainting.push_back(strLine);
		}
	}

	return sourceObjectsToPainting;
}

void Fill(const TCHAR *inputFile, const TCHAR *outputFile)
{
	vector<string> sourceObjectsToPainting = ReadSourceObjectsToPaintingFromFile(inputFile);

	vector<Point> pointsFillMarkers = FindFillMarkers(sourceObjectsToPainting);

	FillObjectsFromPoints(pointsFillMarkers, sourceObjectsToPainting);

	Print(sourceObjectsToPainting, outputFile);
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

