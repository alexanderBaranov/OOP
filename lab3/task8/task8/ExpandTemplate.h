#pragma once
#include <string>
#include <vector>
#include <map>

typedef std::map<std::string, std::string> templateParams;

std::string ExpandTemplate(const std::string& sourceStr, templateParams& tmplParams);