#include "stdafx.h"
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "UrlParser.h"

using namespace std;

static const vector<string> kProtocols = {"http", "https", "ftp"};
static const string kSlashesAfterProtocol = ":////";
static const string kSlash = "//";
static const string kColon = ":";
static const int kMinPort = 1;
static const int kMaxPort = 65535;

Protocol ValidProtocol(string protocolOfUrl)
{
	string lowerProtocol = protocolOfUrl;
	boost::algorithm::to_lower(lowerProtocol);

	auto result = find(kProtocols.begin(), kProtocols.end(), lowerProtocol);

	Protocol protocol = INVALID_PROTOCOL;
	if (result != kProtocols.end())
	{
		if (0 == kProtocols[0].compare(lowerProtocol))
		{
			protocol = HTTP;
		}
		else if (0 == kProtocols[1].compare(lowerProtocol))
		{
			protocol = HTTPS;
		}
		else if (0 == kProtocols[2].compare(lowerProtocol))
		{
			protocol = FTP;
		}
	}

	return protocol;
}

bool ParseURL(std::string const& url,
	Protocol & protocol,
	int & port,
	std::string & host,
	std::string & document)
{
	int posOfSlashesAfterProtocol = url.find_first_of(kSlashesAfterProtocol);
	if (posOfSlashesAfterProtocol == string::npos)
	{
		return false;
	}

	protocol = ValidProtocol(url.substr(0, posOfSlashesAfterProtocol));
	if (protocol ==  INVALID_PROTOCOL)
	{
		return false;
	}

	int posOfBegHost = posOfSlashesAfterProtocol + kSlashesAfterProtocol.length() - 2;
	int posOfSlash = url.find_first_of(kSlash, posOfBegHost);
	string hostWithPort;
	if (posOfSlash == string::npos)
	{
		hostWithPort = url.substr(posOfBegHost);
	}
	else
	{
		hostWithPort = url.substr(posOfBegHost, posOfSlash - posOfBegHost);
		document = url.substr(posOfSlash + 1);
	}
	
	if (hostWithPort.empty())
	{
		return false;
	}

	int posOfColon = hostWithPort.find_first_of(kColon);
	if (posOfColon != string::npos)
	{
		port = stoi(hostWithPort.substr(posOfColon + 1, hostWithPort.length() - posOfColon));
		if ((port < kMinPort) && (port > kMaxPort))
		{
			return false;
		}

		host = hostWithPort.substr(0, posOfColon);
	}
	else
	{
		port = protocol;
		host = hostWithPort;
	}

	return true;
}