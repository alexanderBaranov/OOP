#include "stdafx.h"
#include "UrlParser.h"
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;

static const vector<string> PROTOCOLS = {"http", "https", "ftp"};
static const int MIN_PORT = 1;
static const int MAX_PORT = 65535;

Protocol CheckProtocol(const string& protocolOfUrl)
{
	Protocol protocol;
	if (0 == PROTOCOLS[0].compare(protocolOfUrl))
	{
		protocol = HTTP;
	}
	else if (0 == PROTOCOLS[1].compare(protocolOfUrl))
	{
		protocol = HTTPS;
	}
	else if (0 == PROTOCOLS[2].compare(protocolOfUrl))
	{
		protocol = FTP;
	}

	return protocol;
}

vector<string> ParseFromStringUrlToVector(const string& url)
{
	string processUrl(url);

	boost::regex expression("^(http[s]?|ftp?|HTTP[S]?|FTP)://?([^/:]+)(?::(\\d+))?/?(.+)?");

	vector<string> values;
	boost::regex_split(back_inserter(values), processUrl, expression);

	return values;
}

int GetDefaultPort(Protocol protocol)
{
	return protocol;
}

bool ParseURL(string const& url,
	Protocol& protocol,
	int& port,
	string & host,
	string & document)
{
	vector<string> values = ParseFromStringUrlToVector(url);
	if (values.size() != 4)
	{
		return false;
	}

	boost::algorithm::to_lower(values[0]);
	protocol = CheckProtocol(values[0]);

	port = values[2].length() ? stoi(values[2]) : GetDefaultPort(protocol);
	if ((port < MIN_PORT) || (port > MAX_PORT))
	{
		return false;
	}

	host = values[1];
	document = values[3];

	return true;
}
