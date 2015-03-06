#pragma once
#include <string>
#include <vector>

std::string FilterString(std::vector<std::string>& badWords, std::string inputString);
std::vector<std::string> ReadBadWordsFromFile(const TCHAR *fileName);