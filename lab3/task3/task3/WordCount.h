#pragma once
#include <string>
#include <map>

typedef std::map<std::string, int> mapWords;

mapWords CountWords(const std::string &inputString);
mapWords CountWordsFromFile(const TCHAR* filePath);