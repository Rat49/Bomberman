#pragma once

#include <string>
#include <unordered_map>

struct ConfigFileData {
	bool isPermanent = false;
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> sections;

	ConfigFileData() {}

	ConfigFileData(const bool& isPerm) : isPermanent(isPerm) {}

	ConfigFileData(const bool& isPerm, const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& sections_) :
		isPermanent(isPerm), sections(sections_) {}
};

class ConfigParser {
public:
	ConfigFileData parse(const std::string& configFile, const bool& isPermanent);

private:
	const bool isSection(const std::string& line) const;
};