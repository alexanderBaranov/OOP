// university.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <locale>
#include <windows.h>
#include <atlconv.h>
#include <iostream>
#include "UniversityApp.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 3)
	{
		cout << "Example:university.exe <file_universities.txt> <file_students.txt>" << endl;
		return 1;
	}

	locale::global(locale("rus"));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HANDLE hCon = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	if (hCon != INVALID_HANDLE_VALUE) {
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 0;
		cfi.dwFontSize.Y = 12;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = 400;
		lstrcpyW(cfi.FaceName, L"Lucida Console");
		SetCurrentConsoleFontEx(hCon, FALSE, &cfi);
	}

	try
	{
		USES_CONVERSION;

		CUniversityApp universityApp(make_shared<CUniversityManagement>(W2A(argv[1]), W2A(argv[2])));
		universityApp.Run();
	}
	catch (const exception &error)
	{
		cout << error.what() << endl;
	}
	
	return 0;
}

