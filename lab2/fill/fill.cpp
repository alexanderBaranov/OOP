// fill.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream> 
#include <iostream> 
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

static const char kContur = '#';
static const char kFillMarker = 'o';
static const char kSpace = ' ';
static const char kPoint = '.';
static const int kMaxSize = 100;

struct coordinate
{
	int x;
	int y;

	bool operator==(const coordinate &coord) const
	{
		return (x == coord.x) && (y == coord.y);
	}
};

bool FindEqualCoordinates(const coordinate lastCoord, const vector<coordinate>& contur)
{
	if (!contur.size())
		return false;

	for each (coordinate coord in contur)
	{
		if (coord == lastCoord)
		{
			return true;
		}
	}

	return false;
}

bool IsElementOfContur(
	const coordinate lastCoord,
	const vector<coordinate>& contur,
	const vector<string>& sourceFile)
{
	if (FindEqualCoordinates(lastCoord, contur))
	{
		return true;
	}

	bool halt = true;
	for (size_t i = 0; i < sourceFile.size(); i++)
	{
		if ((i == lastCoord.y)
			&& (lastCoord.x <= (int)sourceFile[i].length())
			&& (sourceFile[i][lastCoord.x] == kContur))
		{
			halt = false;
			break;
		}
	}

	if (halt)
		return true;

	return false;
}

void SetPoint(const vector<coordinate>& contur, vector<string>& sourceFile, int y, int x1, int x2)
{
	for (; x1 < x2; ++x1)
	{
		coordinate temp = { x1, y };
		auto upperBoundOfContur = find_if(contur.begin(), contur.end(), [&temp](coordinate a) 
		{
			return (temp.x == a.x) && (temp.y > a.y);
		});

		if (upperBoundOfContur != contur.end())
		{
			auto lowerBoundOfContur = find_if(contur.begin(), contur.end(), [&temp](coordinate a)
			{
				return (temp.x == a.x) && (temp.y < a.y);
			});

			if (lowerBoundOfContur != contur.end())
			{
				if (sourceFile[y][x1] == kSpace)
				{
					sourceFile[y][x1] = kPoint;
				}
			}
		}
	}	
}

void FillLine(const coordinate& findedCoord, const vector<coordinate>& contur, vector<string>& sourceFile)
{
	for each(coordinate curCoord in contur)
	{
		if ((curCoord.y == findedCoord.y) && (curCoord.x != findedCoord.x))
		{
			if (curCoord.x < findedCoord.x)
			{
				SetPoint(contur, sourceFile, curCoord.y, curCoord.x, findedCoord.x);
			}
			else
			{
				SetPoint(contur, sourceFile, curCoord.y, findedCoord.x, curCoord.x);
			}
		}
	}
}

void FindEnvironment(
	const coordinate coord,
	vector<string>& sourceFile, 
	vector<coordinate>& contur)
{
	coordinate findedCoord;
	bool findedPoint = false;
	if (coord.x != 0)
	{
		if (!findedPoint && !IsElementOfContur({ coord.x - 1, coord.y }, contur, sourceFile))
		{
			findedCoord = {coord.x - 1, coord.y};
			findedPoint = true;
		}
		else if (!findedPoint && !IsElementOfContur({ coord.x - 1, coord.y + 1 }, contur, sourceFile))
		{
			findedCoord = { coord.x - 1, coord.y + 1 };
			findedPoint = true;
		}
	}
	
	if (coord.y != 0)
	{
		if (!findedPoint && !IsElementOfContur({ coord.x, coord.y - 1 }, contur, sourceFile))
		{
			findedCoord = { coord.x, coord.y - 1 };
			findedPoint = true;
		}
		else if (!findedPoint && !IsElementOfContur({ coord.x + 1, coord.y - 1 }, contur, sourceFile))
		{
			findedCoord = { coord.x + 1, coord.y - 1 };
			findedPoint = true;
		}
	}

	if ((coord.x != 0) && (coord.y != 0))
	{
		if (!findedPoint && !IsElementOfContur({ coord.x - 1, coord.y - 1 }, contur, sourceFile))
		{
			findedCoord = { coord.x - 1, coord.y - 1 };
			findedPoint = true;
		}
	}

	if (!findedPoint && !IsElementOfContur({ coord.x + 1, coord.y }, contur, sourceFile))
	{
		findedCoord = { coord.x + 1, coord.y };
		findedPoint = true;
	}
	else if (!findedPoint && !IsElementOfContur({ coord.x, coord.y + 1 }, contur, sourceFile))
	{
		findedCoord = { coord.x, coord.y + 1 };
		findedPoint = true;
	}
	else if (!findedPoint && !IsElementOfContur({ coord.x + 1, coord.y + 1 }, contur, sourceFile))
	{
		findedCoord = { coord.x + 1, coord.y + 1 };
		findedPoint = true;
	}

	if (findedPoint)
	{
		contur.push_back(findedCoord);
		FindEnvironment(findedCoord, sourceFile, contur);
		FillLine(findedCoord, contur, sourceFile);
	}
}

void ConturInline(vector<string>& sourceFile, const int& lineNumber)
{
	const string strInline = sourceFile[lineNumber];
	for (size_t i = 0; i < strInline.length(); i++)
	{
		if (strInline[i] == kFillMarker)
		{
			size_t posOfContur = strInline.find(kContur, i);
			if (posOfContur != string::npos)
			{
				vector<coordinate> contur;
				FindEnvironment({ posOfContur, lineNumber }, sourceFile, contur);

				i = posOfContur;
			}
		}
	}
}

void FindAndFillObjects(vector<string>& sourceFile)
{
	for (size_t i = 0; i < sourceFile.size(); i++)
	{
		ConturInline(sourceFile, i);
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
		if (sourceFile.size() > kMaxSize)
		{
			break;
		}

		if (strLine.length() > kMaxSize)
		{
			sourceFile.push_back(strLine.substr(0, kMaxSize - 1) + "\n");
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

