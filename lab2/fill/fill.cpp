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

typedef std::array<std::array<char, MAX_SIZE>, MAX_SIZE> Canvas;

struct Point
{
	unsigned int x;
	unsigned int y;

	bool operator==(const Point &coord) const
	{
		return (x == coord.x) && (y == coord.y);
	}
};

void TryToPaintThePoint(const Point& point, deque<Point>& paintedPoints, Canvas& canvas)
{
	if ((point.y >= MAX_SIZE)
		|| (point.y < 0)
		|| (point.x >= MAX_SIZE)
		|| (point.x < 0))
	{
		return;
	}

	char& pixel = canvas[point.y][point.x];

	if (pixel == SPACE)
	{
		pixel = POINT;
		paintedPoints.push_back(point);
	}
}

void FillCanvasFromPoint(const Point& point, Canvas& canvas)
{
	deque<Point> paintedPoints = {point};
	while (!paintedPoints.empty())
	{
		const Point& curPoint = paintedPoints.front();

		TryToPaintThePoint({ curPoint.x, curPoint.y + 1 }, paintedPoints, canvas);
		TryToPaintThePoint({ curPoint.x, curPoint.y - 1 }, paintedPoints, canvas);
		TryToPaintThePoint({ curPoint.x + 1, curPoint.y }, paintedPoints, canvas);
		TryToPaintThePoint({ curPoint.x - 1, curPoint.y }, paintedPoints, canvas);

		paintedPoints.pop_front();
	}
}

void FillCanvasFromPoints(const vector<Point>& pointsMarkersFill, Canvas& canvas)
{
	for (const auto& point : pointsMarkersFill)
	{
		FillCanvasFromPoint(point, canvas);
	}
}

vector<Point> FindFillMarkers(const Canvas& canvas)
{
	vector<Point> pointsMarkersFill;
	for (unsigned i = 0; i < canvas.size(); i++)
	{
		const string strLine(canvas[i].data());

		auto & canvasRow = canvas[i];
		for (auto it = canvasRow.begin(); (it = find(it, canvasRow.end(), MARKER_TO_FILL)) != canvasRow.end(); ++it)
		{
			unsigned pos = static_cast<unsigned>(it - canvasRow.begin());
			pointsMarkersFill.push_back({ pos, i });
		}
	}

	return pointsMarkersFill;
}

void Print(const Canvas& canvas, const TCHAR *outputFile)
{
	ofstream outFile(outputFile, ofstream::binary);
	if (!outFile)
	{
		throw exception("Can't open file.");
	}

	for (size_t column = 0; column < canvas.size(); column++)
	{
		for (size_t row = 0; row < canvas[column].size(); row++)
		{
			outFile << canvas[column][row];
		}

		outFile << endl;
	}
}

Canvas ReadCanvasFromFile(const TCHAR *inputFile)
{
	ifstream inFile(inputFile, ifstream::binary);
	if (!inFile)
	{
		throw exception("Can't open file.");
	}

	Canvas canvas;
	canvas[0].fill(' ');
	canvas.fill(canvas[0]);

	int row = 0;
	string line;

	while (getline(inFile, line))
	{
		if (row == MAX_SIZE)
		{
			break;
		}

		string::iterator itEnd = (line.length() <= MAX_SIZE) ? line.end() : line.begin() + MAX_SIZE;

		transform(line.begin(), itEnd, canvas[row].begin(), [](char ch)
		{
			if ((ch == '\n') || (ch == '\r'))
			{
				ch = ' ';
			}

			return ch;
		});

		row++;
	}

	return canvas;
}

void Fill(const TCHAR *inputFile, const TCHAR *outputFile)
{
	Canvas canvas = ReadCanvasFromFile(inputFile);

	vector<Point> pointsFillMarkers = FindFillMarkers(canvas);

	FillCanvasFromPoints(pointsFillMarkers, canvas);

	Print(canvas, outputFile);
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
	catch (const exception& e)
	{
		cout << e.what();
	}

	return 0;
}

