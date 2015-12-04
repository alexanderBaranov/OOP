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
	cout << "Input URLs. Ctrl+z is close input URLs." << endl;
	cout << "URLs: ";

	Protocol protocol;
	int port;
	string host;
	string document;

	istringstream urls(string(istream_iterator<char>(cin >> noskipws), istream_iterator<char>()));
	string url;
	while (urls >> url)
	{
		cout << url << endl;
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
	}

	return 0;
}

