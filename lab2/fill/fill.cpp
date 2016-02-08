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
#include <array>
#include <boost/utility/string_ref.hpp>

using namespace std;

static const char CONTOUR = '#';
static const char MARKER_TO_FILL = 'o';
static const char SPACE = ' ';
static const char POINT = '.';
static const int MAX_SIZE = 100;

typedef std::array<std::array<char, MAX_SIZE>, MAX_SIZE> dataArray;

struct Point
{
	unsigned int x;
	unsigned int y;

	bool operator==(const Point &coord) const
	{
		return (x == coord.x) && (y == coord.y);
	}
};

void TryToAddPointToPainting(const Point& point, deque<Point>& pointsToBePainted, const dataArray& sourceObjectsToPaint)
{
	if ((point.y >= MAX_SIZE)
		|| (point.y < 0)
		|| (point.x >= MAX_SIZE)
		|| (point.x < 0))
	{
		return;
	}

	if (sourceObjectsToPaint[point.y][point.x] == SPACE)
	{
		if (!(find(pointsToBePainted.begin(), pointsToBePainted.end(), point) != pointsToBePainted.end()))
		{
			pointsToBePainted.push_back(point);
		}
	}
}

void FillObjectFromPoint(const Point& point, dataArray& sourceObjectsToPaint)
{
	deque<Point> pointsToBePainted = {point};
	while (!pointsToBePainted.empty())
	{
		const Point& curPoint = pointsToBePainted.front();
		char& contentsOfPoint = sourceObjectsToPaint[curPoint.y][curPoint.x];

		if (contentsOfPoint == SPACE)
		{
			contentsOfPoint = POINT;
		}

		TryToAddPointToPainting({ curPoint.x, curPoint.y + 1 }, pointsToBePainted, sourceObjectsToPaint);
		TryToAddPointToPainting({ curPoint.x, curPoint.y - 1}, pointsToBePainted, sourceObjectsToPaint);
		TryToAddPointToPainting({ curPoint.x + 1, curPoint.y }, pointsToBePainted, sourceObjectsToPaint);
		TryToAddPointToPainting({ curPoint.x - 1, curPoint.y }, pointsToBePainted, sourceObjectsToPaint);

		pointsToBePainted.pop_front();
	}
}

void FillObjectsFromPoints(const vector<Point>& pointsMarkersFill, dataArray& sourceObjectsToPaint)
{
	for (const auto& point : pointsMarkersFill)
	{
		FillObjectFromPoint(point, sourceObjectsToPaint);
	}
}

vector<Point> FindFillMarkers(const dataArray& sourceObjectsToPaint)
{
	vector<Point> pointsMarkersFill;
	for (size_t i = 0; i < sourceObjectsToPaint.size(); i++)
	{
		const string strLine(sourceObjectsToPaint[i].data());

		auto it = find(sourceObjectsToPaint[i].begin(), sourceObjectsToPaint[i].end(), MARKER_TO_FILL);
		while (it != sourceObjectsToPaint[i].end())
		{
			size_t pos = it - sourceObjectsToPaint[i].begin();
			pointsMarkersFill.push_back({ pos, i });
			it = find(it + 1, sourceObjectsToPaint[i].end(), MARKER_TO_FILL);
		}
	}

	return pointsMarkersFill;
}

void Print(dataArray& sourceObjectsToPaint, const TCHAR *outputFile)
{
	ofstream outFile(outputFile, ofstream::binary);
	if (!outFile)
	{
		throw exception("Can't open file.");
	}

	for (size_t column = 0; column < sourceObjectsToPaint.size(); column++)
	{
		for (size_t row = 0; row < sourceObjectsToPaint[column].size(); row++)
		{
			outFile << sourceObjectsToPaint[column][row];
		}

		outFile << endl;
	}
}

dataArray ReadSourceObjectsToPaintingFromFile(const TCHAR *inputFile)
{
	ifstream inFile(inputFile, ifstream::binary);
	if (!inFile)
	{
		throw exception("Can't open file.");
	}

	dataArray sourceObjectsToPaint;
	sourceObjectsToPaint[0].fill(' ');
	sourceObjectsToPaint.fill(sourceObjectsToPaint[0]);

	int column = 0;
	string line;

	while (getline(inFile, line))
	{
		if (column == MAX_SIZE)
		{
			break;
		}

		line = line.substr(0, MAX_SIZE);

		copy_if(line.begin(), line.end(), sourceObjectsToPaint[column].begin(), [](char& ch)
		{
			if ((ch == '\n') || (ch == '\r'))
			{
				ch = ' ';
			}
			return ch;
		});

		column++;
	}

	return sourceObjectsToPaint;
}

void Fill(const TCHAR *inputFile, const TCHAR *outputFile)
{
	dataArray sourceObjectsToPaint = ReadSourceObjectsToPaintingFromFile(inputFile);

	vector<Point> pointsFillMarkers = FindFillMarkers(sourceObjectsToPaint);

	FillObjectsFromPoints(pointsFillMarkers, sourceObjectsToPaint);

	Print(sourceObjectsToPaint, outputFile);
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

