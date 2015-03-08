#include "stdafx.h"
#include "UrlParser.h"
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;

static const vector<string> kProtocols = {"http", "https", "ftp"};
static const int kMinPort = 1;
static const int kMaxPort = 65535;

Protocol CheckProtocol(string protocolOfUrl)
{
	Protocol protocol;
	if (0 == kProtocols[0].compare(protocolOfUrl))
	{
		protocol = HTTP;
	}
	else if (0 == kProtocols[1].compare(protocolOfUrl))
	{
		protocol = HTTPS;
	}
	else if (0 == kProtocols[2].compare(protocolOfUrl))
	{
		protocol = FTP;
	}

	return protocol;
}

vector<string> ParseFromStringUrlToVector(const string url)
{
	string processUrl(url);
	boost::algorithm::to_lower(processUrl);

	boost::regex expression("^(http[s]?|ftp):\/\/?([^/\:]+)(?::(\\d+))?\/?(.+)?");

	if (!boost::regex_match(processUrl, expression))
	{
		return {};
	}

	vector<string> values;
	if (!boost::regex_split(back_inserter(values), processUrl, expression))
	{
		return {};
	}

	return values;
}

bool ParseURL(string const& url,
	Protocol & protocol,
	int & port,
	string & host,
	string & document)
{
	vector<string> values = ParseFromStringUrlToVector(url);
	if (values.empty())
	{
		return false;
	}

	protocol = CheckProtocol(values[0]);
	port = values[2].length() ? stoi(values[2]) : protocol;
	if ((port <= kMinPort) && (port >= kMaxPort))
	{
		return false;
	}

	host = values[1];
	document = values[3];

	return true;
}
