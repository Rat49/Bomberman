#pragma once

#include <string>
#include <unordered_map>
#include "ConfigFile.hpp"

class ConfigParser {
public:
	void parse(ConfigFile& configFile) const;

private:
	bool isSection(const std::string& line) const;
};