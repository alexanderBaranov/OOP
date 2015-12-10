#pragma once
#include <string>
#include <vector>

std::string FilterString(const std::vector<std::string>& badWords, const std::string& inputString);
std::vector<std::string> ReadBadWordsFromFile(const std::string& fileName);
std::vector<std::string> ParseWordsToVector(std::string line);
std::string Filter(const std::string& fileName, const std::string& inputString);