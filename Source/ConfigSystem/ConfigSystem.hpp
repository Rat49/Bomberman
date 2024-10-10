#pragma once

#include <string>
#include <unordered_map>
#include "ConfigParser.hpp"

class ConfigSystem {
public:

	void addFile(const std::string& configFile, const bool& isPermanent, ConfigFileData& fileData);

	void removeFile(std::string configFile);

	const bool isFilePresent(const std::string& configFile) const;

	const bool isSectionPresent(const std::string& configFile, const std::string& sectionName) const;

	const bool isValuePresent(const std::string& configFile, const std::string& sectionName, const std::string& valueName) const;

	const std::string& getValue(const std::string& configFile, const std::string& sectionName, const std::string& valueName) const;

	void setValue(const std::string& configFile, const std::string& sectionName, const std::string& valueName, const std::string& value);

	void deleteTemporaryFiles();

	void printConfigFile(const std::string& configFile) const;

private:
	std::unordered_map<std::string, ConfigFileData> configFiles;

	ConfigParser parser;
};