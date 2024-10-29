#pragma once
#include <string>
#include <vector>
#include <sstream>

class StringUtils
{
public:
	static std::vector<std::string> explode(const std::string& textToExplode, char delim);
};

