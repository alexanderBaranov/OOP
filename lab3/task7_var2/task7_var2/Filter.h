#pragma once
#include <string>
#include <vector>
#include <unordered_set>

std::string FilterString(const std::unordered_set<std::string>& badWords, const std::string& inputString);
std::unordered_set<std::string> ReadBadWordsFromFile(const std::string& fileName);
std::unordered_set<std::string> ParseWordsToVector(std::string line);
std::string Filter(const std::string& fileName, const std::string& inputString);