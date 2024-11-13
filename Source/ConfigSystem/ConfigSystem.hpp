#pragma once

#include <string>
#include <unordered_map>
#include "ConfigParser.hpp"
#include "ConfigFile.hpp"
#include "BaseModule/BaseModule.hpp"

class ConfigSystem : public BaseModule
{
public:

	const ConfigFile& ConfigSystem::getFile(const std::string& configFile) const;

	void ConfigSystem::addFile(const std::string& configFile);

	void removeFile(const std::string& configFile);

	bool isFilePresent(const std::string& configFile) const;

	bool isSectionPresent(const std::string& configFile, const std::string& sectionName) const;

	bool isValuePresent(const std::string& configFile, const std::string& sectionName, const std::string& valueName) const;

	bool areValuesPresent(const std::string& configFile, const std::string& sectionName, const std::vector<std::string>& keys) const;

	const ConfigValue& getValue(const std::string& configFile, const std::string& sectionName, const std::string& valueName) const;

	void setValue(const std::string& configFile, const std::string& sectionName, const std::string& valueName, const std::string& value);

	void terminate() override;

private:
	std::unordered_map<std::string, ConfigFile> configFiles;

	ConfigParser parser;
};
