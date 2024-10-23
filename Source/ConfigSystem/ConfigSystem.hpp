#pragma once

#include <string>
#include <unordered_map>
#include "ConfigParser.hpp"
#include "ConfigFile.hpp"

enum class FileName {
	configTest,
	WalkingAnimation,
	questSystem
};

class ConfigSystem {
public:

	ConfigSystem();

	ConfigFile& getFile(const FileName& configFile) const;

	void removeFile(const FileName& configFile);

	bool isFilePresent(const FileName& configFile) const;

	bool isSectionPresent(const FileName& configFile, const std::string& sectionName) const;

	bool isValuePresent(const FileName& configFile, const std::string& sectionName, const std::string& valueName) const;

	bool areValuesPresent(const FileName& configFile, const std::string& sectionName, const std::vector<std::string>& keys) const;

	const ConfigValue& getValue(const FileName& configFile, const std::string& sectionName, const std::string& valueName) const;

	void setValue(const FileName& configFile, const std::string& sectionName, const std::string& valueName, const std::string& value);

private:
	static std::unordered_map<FileName, ConfigFile> configFiles;

	ConfigParser parser;
};
