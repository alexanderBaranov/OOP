// task6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream> 
#include <string>
#include <algorithm>
#include "Dictionary.h"
#include <boost/algorithm/string.hpp>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 2)
	{
		cout << "Example: task6.exe <input file>";
		return 1;
	}

	try
	{
		dictionary dict = ReadDictionaryFromFile(argv[1]);

		string inputString, keyForValue;
		bool findExpression = true;
		bool isChanded = false;
		while (inputString != "...")
		{
			getline(cin, inputString);

			if (!findExpression)
			{
				if (!inputString.empty())
				{
					isChanded = true;
					dict[keyForValue] = inputString;

					cout << "Слово \"" << keyForValue << "\" сохранено в словаре как \"" << inputString << "\"." << endl;
				}
				else
				{
					cout << "Слово " << keyForValue << " проигнорировано." << endl;
				}

				findExpression = true;
			}
			else
			{
				if (inputString == "...")
				{
					cout << "В словарь были внесены изменения.Введите Y или y для сохранения перед выходом." << endl;

					string end;
					cin >> end;

					boost::algorithm::to_lower(end);
					if (end == "y")
					{
						WriteToDictionaryFile(argv[1], dict);
					}
				}

				string value = GetValueFromDictionary(dict, inputString);

				if (value.empty())
				{
					cout << "Неизвестное слово " << inputString << "введите перевод или пустую строку для отказа." << endl;

					keyForValue = inputString;
					findExpression = false;
				}
				else
				{
					cout << value << endl;
				}
			}
		}
	}
	catch (exception e)
	{
		cout << e.what();
	}

	return 0;
}

