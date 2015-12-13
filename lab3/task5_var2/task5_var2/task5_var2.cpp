// task5_var2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "UrlParser.h"
#include <sstream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Input URLs. 'exit' is close programm." << endl;

	Protocol protocol;
	int port;
	string host;
	string document;

	cout << "URL: ";

	string url;
	while( getline(cin, url) )
	{
		if (url.compare("exit") == 0)
		{
			break;
		}

		if (!ParseURL(url, protocol, port, host, document))
		{
			cout << "Invalid url" << endl;
		}
		else
		{
			cout << "HOST:" << host << endl;
			cout << "PORT:" << port << endl;
			cout << "DOC:" << document << endl << endl;
		}

		cout << "URL: ";
	}

	return 0;
}

