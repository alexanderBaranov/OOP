// CStringList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include "StringList.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::list<std::string> lst;
	auto b = lst.begin();
	lst.push_back("hello");
	return 0;
}
