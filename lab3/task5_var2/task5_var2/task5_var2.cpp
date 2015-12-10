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

	//istringstream urls(string(istream_iterator<char>(cin >> noskipws), istream_iterator<char>()));
	//string url;
	//while (urls >> url)
	//{
	//	cout << url << endl;
	//	if (!ParseURL(url, protocol, port, host, document))
	//	{
	//		cout << "Invalid url" << endl;
	//	}
	//	else
	//	{
	//		cout << "HOST:" << host << endl;
	//		cout << "PORT:" << port << endl;
	//		cout << "DOC:" << document << endl << endl;
	//	}
	//}

	//istream_iterator<char>in_it;
	//do{
	//	cout << "Input url(Ctrl+z is close input url. Input only '.' and Ctrl+z exit programm): ";
	//	cin.clear();

	//	in_it = cin >> noskipws;
	//	string url(in_it, istream_iterator<char>());

	//	cout << url << endl;
	//	if (!ParseURL(url, protocol, port, host, document))
	//	{
	//		cout << "Invalid url" << endl;
	//	}
	//	else
	//	{
	//		cout << "HOST:" << host << endl;
	//		cout << "PORT:" << port << endl;
	//		cout << "DOC:" << document << endl << endl;
	//	}

	//} while (*in_it != '.');

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

