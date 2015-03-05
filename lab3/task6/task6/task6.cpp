// task6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream> 
#include <string>
#include <algorithm>
#include "Dictionary.h"
#include <boost/algorithm/string.hpp>
#include<clocale>
#include <codecvt>

using namespace std;

void SetNewExpression(dictionary& dict, string& key)
{
	cout << "Неизвестное слово " << key << " введите перевод или пустую строку для отказа." << endl;

	string newValue;
	getline(cin,newValue);

	if (!newValue.empty())
	{
		dict[key] = newValue;

		cout << "Слово \"" << key << "\" сохранено в словаре как \"" << newValue << "\"." << endl;
	}
	else
	{
		cout << "Слово " << key << " проигнорировано." << endl;
	}
}

bool Translate(dictionary& dict, string key)
{
	string value = GetValueFromDictionary(dict, key);

	if (!value.empty())
	{
		cout << value << endl;
	}

	return !value.empty() ? true : false;
}

void WriteNewDictionary(dictionary& dict, const TCHAR *fileName)
{
	cout << "В словарь были внесены изменения.Введите Y или y для сохранения перед выходом." << endl;

	string end;
	cin >> end;

	boost::algorithm::to_lower(end);
	if (end == "y")
	{
		if (WriteToDictionaryFile(fileName, dict))
		{
			cout << "Изменения сохранены. До свидания." << endl;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 2)
	{
		cout << "Example: task6.exe <input file>";
		return 1;
	}

	setlocale(LC_CTYPE, "");

	try
	{
		dictionary dict = ReadDictionaryFromFile(argv[1]);
		dictionary newExpressions;
		string inputString;

		while (true)
		{
			getline(cin, inputString);

			if (inputString == "...")
			{
				break;
			}

			if (!Translate(dict, inputString))
			{
				SetNewExpression(newExpressions, inputString);
				dict.insert(newExpressions.begin(), newExpressions.end());
			}
		}

		if (newExpressions.size())
		{
			WriteNewDictionary(newExpressions, argv[1]);
		}
	}
	catch (exception e)
	{
		cout << e.what();
	}

	return 0;
}

