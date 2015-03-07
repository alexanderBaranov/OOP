#pragma once
#include <string>
#include <vector>

std::string FilterString(std::vector<std::string>& badWords, std::string inputString);
std::vector<std::string> ReadBadWordsFromFile(const TCHAR *fileName);
std::vector<std::string> GetExpression(std::string line);
std::string Filter(const TCHAR *fileName, std::string inputString);