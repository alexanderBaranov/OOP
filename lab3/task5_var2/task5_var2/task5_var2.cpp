// task5_var2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "UrlParser.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "URL: ";

	string url;
	cin >> url;

	Protocol protocol;
	int port;
	string host;
	string document;

	if (!ParseURL(url, protocol, port, host, document))
	{
		cout << "Invalid url" << endl;
		return 1;
	}

	cout << url << endl;
	cout << "HOST:" << host << endl;
	cout << "PORT:" << port<< endl;
	cout << "DOC:" << document << endl;

	return 0;
}

