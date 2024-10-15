#pragma once

#include <string>
#include <unordered_map>
#include "ConfigParser.hpp"
#include "ConfigFile.hpp"

class ConfigSystem {
public:

	void addFile(ConfigFile& fileData);

	void removeFile(const std::string& configFile);

	bool isFilePresent(const std::string& configFile) const;

	bool isSectionPresent(const std::string& configFile, const std::string& sectionName) const;

	bool isValuePresent(const std::string& configFile, const std::string& sectionName, const std::string& valueName) const;

	const ConfigValue& getValue(const std::string& configFile, const std::string& sectionName, const std::string& valueName) const;

	void setValue(const std::string& configFile, const std::string& sectionName, const std::string& valueName, const std::string& value);

private:
	std::unordered_map<std::string, ConfigFile> configFiles;

	ConfigParser parser;
};