#pragma once

#include <string>
#include <unordered_map>
#include "FileData.hpp"

class ConfigParser {
public:
	const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& parse(const FileData::ConfigFileName& configFile, FileData& data);

private:
	const bool isSection(const std::string& line) const;
};