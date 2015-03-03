// TestOfTask5Var2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_TEST_MODULE TestsOfTask1Var8

#include <boost\test\included\unit_test.hpp>
#include "..\task5_var2\UrlParser.h"
#include <string>

using namespace std;

BOOST_AUTO_TEST_SUITE(TestsOfTask5Var2)

void Test(const string url, 
		const int portEqual, 
		const Protocol protocolEqual,
		const string hostEqual,
		const string documentEqual)
{
	Protocol protocol;
	int port;
	string host;
	string document;

	BOOST_CHECK(ParseURL(url, protocol, port, host, document));
	BOOST_CHECK_EQUAL(port, portEqual);
	BOOST_CHECK_EQUAL(protocol, protocolEqual);
	BOOST_CHECK_EQUAL(host, hostEqual);
	BOOST_CHECK_EQUAL(document, documentEqual);
}

BOOST_AUTO_TEST_CASE(testStringOperations)
{
	Test("HTTP://vk", 80, HTTP, "vk", "");
	Test("http://vk", 80, HTTP, "vk", "");
	Test("http://vk.com", 80, HTTP, "vk.com", "");
	Test("http://vk.vk.com:23", 23, HTTP, "vk.vk.com", "");
	Test("http://vk.vk.com/a/b/c/d", 80, HTTP, "vk.vk.com", "a/b/c/d");

	Test("HTTPS://vk", 443, HTTPS, "vk", "");
	Test("https://vk", 443, HTTPS, "vk", "");
	Test("https://vk.vk.com", 443, HTTPS, "vk.vk.com", "");
	Test("https://vk.vk.com:23", 23, HTTPS, "vk.vk.com", "");
	Test("https://vk.vk.com/a/b/c/d", 443, HTTPS, "vk.vk.com", "a/b/c/d");

	Test("FTP://vk", 21, FTP, "vk", "");
	Test("ftp://vk", 21, FTP, "vk", "");
	Test("ftp://vk.vk.com", 21, FTP, "vk.vk.com", "");
	Test("ftp://vk.vk.com:23", 23, FTP, "vk.vk.com", "");
	Test("ftp://vk.vk.com/a/b/c/d", 21, FTP, "vk.vk.com", "a/b/c/d");

	Protocol protocol;
	int port;
	string host;
	string document;

	BOOST_CHECK(!ParseURL("http://", protocol, port, host, document));
	BOOST_CHECK(!ParseURL("https://", protocol, port, host, document));
	BOOST_CHECK(!ParseURL("ftp://", protocol, port, host, document));
}

BOOST_AUTO_TEST_SUITE_END()

