// task6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <algorithm>
#include "Dictionary.h"
#include <boost/algorithm/string.hpp>
#include <locale>
#include <conio.h>

using namespace std;

void AddNewTranslationMessageToDictionary(dictionary& dict, string message, string translationMessage)
{
	boost::algorithm::to_lower(message);
	dict[message] = translationMessage;
}

void SetNewTranslationMessage(dictionary& dict, const string& message)
{
	cout << "Неизвестное слово " << message << " введите перевод или пустую строку для отказа." << endl;

	string translationMessage;
	getline(cin, translationMessage);

	if (!translationMessage.empty())
	{
		AddNewTranslationMessageToDictionary(dict, message, translationMessage);

		cout << "Слово \"" << message << "\" сохранено в словаре как \"" << translationMessage << "\"." << endl;
	}
	else
	{
		cout << "Слово " << message << " проигнорировано." << endl;
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

void SetupConsoleFont(const HANDLE& hConsole, CONSOLE_FONT_INFOEX cfi)
{
	if (hConsole != INVALID_HANDLE_VALUE)
	{
		SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 2)
	{
		cout << "Example: task6.exe <input file>";
		return 1;
	}

	int cp = GetConsoleCP();
	int cpOutput = GetConsoleOutputCP();

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	CONSOLE_FONT_INFOEX curCfi, newCfi;

	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	if (hConsole != INVALID_HANDLE_VALUE)
	{
		GetCurrentConsoleFontEx(hConsole, FALSE, &curCfi);
		newCfi = curCfi;

		wcscpy_s(newCfi.FaceName, L"Lucida Console");

		SetupConsoleFont(hConsole, newCfi);
	}

	cout << "'...' is exit programm.\n" << endl;

	try
	{
		_TCHAR* dictionaryFileName = argv[1];

		dictionary dict = ReadDictionaryFromFile(dictionaryFileName);
		string inputString;
		size_t sizeOfDictionary = dict.size();

		while (true)
		{
			getline(cin, inputString);

			if (inputString == "...")
			{
				break;
			}

			if (!Translate(dict, inputString))
			{
				SetNewTranslationMessage(dict, inputString);
			}
		}

		if (sizeOfDictionary != dict.size())
		{
			WriteNewDictionary(dict, dictionaryFileName);
		}
	}
	catch (const exception& e)
	{
		cout << e.what();
	}

	SetConsoleCP(cp);
	SetConsoleOutputCP(cpOutput);
	SetupConsoleFont(hConsole, curCfi);

	return 0;
}
