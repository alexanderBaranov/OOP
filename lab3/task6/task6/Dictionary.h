#pragma once
#include <string>
#include <map>
#include <vector>
#include <sstream>

typedef std::map<std::string, std::string> dictionary;

dictionary ReadDictionaryFromFile(const TCHAR *infileStream);
dictionary GetDictionaryFromStream(std::istream& inputStream);

bool WriteToDictionaryFile(const TCHAR *outFileStream, dictionary& dict);
std::ostringstream GetStreamFromDictionary(const dictionary& dict);

std::string GetValueFromDictionary(const dictionary &dict, std::string key);