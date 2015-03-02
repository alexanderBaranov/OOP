#pragma once
#include <string>
#include <map>

typedef std::map<std::string, int> mapWords;

mapWords WordCount(std::string inputString);