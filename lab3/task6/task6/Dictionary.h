#pragma once
#include <string>
#include <map>
#include <vector>

typedef std::map<std::string, std::string> dictionary;

dictionary ReadDictionaryFromFile(const TCHAR *fileName);

bool WriteToDictionaryFile(const TCHAR *fileName, dictionary dict);

std::vector<std::string> GetExpression(std::string line);

std::string GetValueFromDictionary(dictionary &dict, std::string key);