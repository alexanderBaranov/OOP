#pragma once
#include <string>
#include <vector>
#include <map>
#include <boost/utility/string_ref.hpp>

typedef std::map<boost::string_ref, boost::string_ref> templateParams;

std::string ExpandTemplate(const std::string& sourceStr, const templateParams& tmplParams);