#pragma once
#include <string>
#include <map>

typedef std::map<std::string, int> mapWords;

mapWords WordCount(const std::string &inputString);