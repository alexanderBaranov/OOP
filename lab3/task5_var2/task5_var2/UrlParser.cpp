#include "stdafx.h"
#include "UrlParser.h"
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;

static const map<string, Protocol> PROTOCOLS = {{ "http", HTTP }, { "https", HTTPS }, { "ftp", FTP }};
static const int MIN_PORT = 1;
static const int MAX_PORT = 65535;

Protocol CheckProtocol(const string& protocolOfUrl)
{	
	auto it = PROTOCOLS.find(protocolOfUrl);

	return it != PROTOCOLS.end() ? it->second : UNKNOWN_HOST;
}

vector<string> ParseFromStringUrlToVector(const string& url)
{
	string processUrl(url);

	boost::regex expression("^(.+)://?([^/:]+)(?::(\\d+))?/?(.+)?");

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
	if (protocol == UNKNOWN_HOST)
	{
		return false;
	}

	port = values[2].length() ? stoi(values[2]) : GetDefaultPort(protocol);
	if ((port < MIN_PORT) || (port > MAX_PORT))
	{
		return false;
	}

	host = values[1];
	document = values[3];

	return true;
}
