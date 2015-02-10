// multmatrix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream> 
#include <iostream> 
#include <string>
#include <array>
#include <sstream>
#include <map>
#include <vector>
using namespace std;

typedef vector<vector<float>> Matrix;

Matrix ReadMatrix(const TCHAR *filePath)
{
	Matrix matrix = {};
	ifstream inputFile(filePath);
	if (!inputFile)
	{
		throw invalid_argument("Can't open file.");
	}

	while (!inputFile.eof())
	{
		string strLine;
		getline(inputFile, strLine);

		istringstream strStream(strLine);
		string word;
		int col = 0;
		vector<float> rows;
		while (strStream >> word)
		{
			rows.push_back(stof(word));
			col++;
		}
		matrix.push_back(rows);
	}

	inputFile.close();

	return matrix;
}

Matrix MultMatrix(Matrix& matrix1, Matrix& matrix2)
{
	Matrix resultMatrix = {};

	int colMatrix1 = matrix1[0].size();
	int rowMatrix1 = matrix1.size();
	int rowMatrix2 = matrix2.size();
	int colMatrix2 = matrix2[0].size();
	for (int curRow = 0; curRow < rowMatrix1; curRow++)
	{
		vector<float> rows(colMatrix2);
		for (int curCol = 0; curCol < colMatrix2; curCol++)
		{
			for (int multRow = 0; multRow < rowMatrix2; multRow++)
			{
				rows[curCol] += matrix1[curRow][multRow] * matrix2[multRow][curCol];
			}
		}
		resultMatrix.push_back(rows);
	}

	return resultMatrix;
}

void PrintMatrix(Matrix& matrix)
{
	for each (auto column in matrix)
	{
		for_each(column.begin(), column.end(), [] (float value)
		{
			cout << value << " ";
		});

		cout << "\n";
	}
}

void MultMatrix(const TCHAR *matrixFile1, const TCHAR *matrixFile2)
{
	try
	{
		auto matrix1 = ReadMatrix(matrixFile1);
		auto matrix2 = ReadMatrix(matrixFile2);

		size_t col = matrix1[0].size();
		size_t row = matrix2.size();

		if (col != row)
		{
			cout << "Colum of matrix 1 don't equal with row of matrix 2.";
			return;
		}

		auto resultMatrix = MultMatrix(matrix1, matrix2);
		PrintMatrix(resultMatrix);
	}
	catch (const invalid_argument& error)
	{
		cout << error.what() << '\n';
		return;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 3)
	{
		cout << "Example: multmatrix.exe <matrix file1> <matrix file2>";
		return 1;
	}

	MultMatrix(argv[1], argv[2]);

	return 0;
}

