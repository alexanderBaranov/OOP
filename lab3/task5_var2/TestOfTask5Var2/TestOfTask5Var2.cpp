// TestOfTask5Var2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_TEST_MODULE TestsOfTask1Var8

#include <boost\test\included\unit_test.hpp>
#include "..\task5_var2\UrlParser.h"
#include <string>

using namespace std;

BOOST_AUTO_TEST_SUITE(TestsOfTask5Var2)

void TestParseUrlAndEqualWithExpectedValues(const string& url,
		const int expectedPort, 
		const Protocol expectedProtocol,
		const string& expectedHost,
		const string& expectedDocument)
{
	Protocol protocol;
	int port;
	string host;
	string document;

	BOOST_CHECK(ParseURL(url, protocol, port, host, document));
	BOOST_CHECK_EQUAL(port, expectedPort);
	BOOST_CHECK_EQUAL(protocol, expectedProtocol);
	BOOST_CHECK_EQUAL(host, expectedHost);
	BOOST_CHECK_EQUAL(document, expectedDocument);
}

bool CheckValidityOfAddress(const string& url)
{
	Protocol protocol;
	int port;
	string host;
	string document;

	return ParseURL(url, protocol, port, host, document);
}

BOOST_AUTO_TEST_CASE(test_checking_the_validity_of_url_consisting_only_scheme)
{
	BOOST_CHECK(!CheckValidityOfAddress("http://"));
	BOOST_CHECK(!CheckValidityOfAddress("https://"));
	BOOST_CHECK(!CheckValidityOfAddress("ftp://"));
}

BOOST_AUTO_TEST_CASE(test_check_empty_url)
{
	BOOST_CHECK(!CheckValidityOfAddress(" "));
}

BOOST_AUTO_TEST_CASE(test_invalid_url)
{
	BOOST_CHECK(!CheckValidityOfAddress("BBC://1tv.ru"));
}

BOOST_AUTO_TEST_CASE(test_non_existen_port)
{
	BOOST_CHECK(!CheckValidityOfAddress("HTTP:://1tv.ru:0"));
	BOOST_CHECK(!CheckValidityOfAddress("HTTP:://1tv.ru:70000"));
}

BOOST_AUTO_TEST_CASE(test_check_url_with_ip)
{
	TestParseUrlAndEqualWithExpectedValues("HTTP://192.168.1.1", 80, HTTP, "192.168.1.1", "");
}

BOOST_AUTO_TEST_CASE(test_parse_HTTP_url)
{
	TestParseUrlAndEqualWithExpectedValues("HTTP://vk", 80, HTTP, "vk", "");
	TestParseUrlAndEqualWithExpectedValues("http://vk", 80, HTTP, "vk", "");
	TestParseUrlAndEqualWithExpectedValues("http://vk.com", 80, HTTP, "vk.com", "");
	TestParseUrlAndEqualWithExpectedValues("http://vk.vk.com:23", 23, HTTP, "vk.vk.com", "");
	TestParseUrlAndEqualWithExpectedValues("http://vk.vk.com/a/b/c/d", 80, HTTP, "vk.vk.com", "a/b/c/d");
}

BOOST_AUTO_TEST_CASE(test_parse_HTTPS_url)
{
	TestParseUrlAndEqualWithExpectedValues("HTTPS://vk", 443, HTTPS, "vk", "");
	TestParseUrlAndEqualWithExpectedValues("https://vk", 443, HTTPS, "vk", "");
	TestParseUrlAndEqualWithExpectedValues("https://vk.vk.com", 443, HTTPS, "vk.vk.com", "");
	TestParseUrlAndEqualWithExpectedValues("https://vk.vk.com:23", 23, HTTPS, "vk.vk.com", "");
	TestParseUrlAndEqualWithExpectedValues("https://vk.vk.com/a/b/c/d", 443, HTTPS, "vk.vk.com", "a/b/c/d");
}

BOOST_AUTO_TEST_CASE(test_parse_FTP_url)
{
	TestParseUrlAndEqualWithExpectedValues("FTP://vk", 21, FTP, "vk", "");
	TestParseUrlAndEqualWithExpectedValues("ftp://vk", 21, FTP, "vk", "");
	TestParseUrlAndEqualWithExpectedValues("ftp://vk.vk.com", 21, FTP, "vk.vk.com", "");
	TestParseUrlAndEqualWithExpectedValues("ftp://vk.vk.com:23", 23, FTP, "vk.vk.com", "");
	TestParseUrlAndEqualWithExpectedValues("ftp://vk.vk.com/a/b/c/d", 21, FTP, "vk.vk.com", "a/b/c/d");
}

BOOST_AUTO_TEST_SUITE_END()

