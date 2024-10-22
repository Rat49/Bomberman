#include "ConfigSystem.hpp"
#include <iostream>

std::unordered_map<FileName, ConfigFile> ConfigSystem::configFiles = {
	{FileName::configTest, ConfigFile("../../Data/Config/config.ini")},
	{FileName::WalkingAnimation, ConfigFile("../../Data/Config/WalkingAnimation.ini")}
	//{FileName::questSystem, ConfigFile("../../Data/Config/questSystem.ini")} -> will be added after merge
};

ConfigSystem::ConfigSystem()
{
	for (auto& files : configFiles) {
		parser.parse(files.second);
	}
}

ConfigFile& ConfigSystem::getFile(const FileName& configFile) const
{
	return configFiles[configFile];
}

void ConfigSystem::removeFile(const FileName& configFile)
{
	configFiles.erase(configFile);
}

bool ConfigSystem::isFilePresent(const FileName& configFile) const
{
	return configFiles.find(configFile) != configFiles.end();
}

bool ConfigSystem::isSectionPresent(const FileName& configFile, const std::string& sectionName) const
{
	if (isFilePresent(configFile)) {
		auto it = configFiles.find(configFile);
		return it->second.isSectionPresent(sectionName);
	}
	return false;
}

bool ConfigSystem::isValuePresent(const FileName& configFile, const std::string& sectionName, const std::string& valueName) const
{
	if (isSectionPresent(configFile, sectionName)) {
		auto it = configFiles.find(configFile);
		auto& it2 = it->second.getSection(sectionName);
		return it2.isValuePresent(valueName);
	}
	return false;
}

bool ConfigSystem::areValuesPresent(const FileName& configFile, const std::string& sectionName, const std::vector<std::string>& keys) const
{
	for(const auto& key: keys) {
		if (!isValuePresent(configFile, sectionName, key)) return false;
	}
	return true;
}

const ConfigValue& ConfigSystem::getValue(const FileName& configFile, const std::string& sectionName, const std::string& valueName) const
{
	if (isValuePresent(configFile, sectionName, valueName)) {
		auto it = configFiles.find(configFile);
		auto& it2 = it->second.getSection(sectionName);
		return it2.getValue(valueName);
	}
	else {
		static const ConfigValue defaultValue;
		return defaultValue;
	}
}

void ConfigSystem::setValue(const FileName& configFile, const std::string& sectionName, const std::string& valueName, const std::string& value)
{
	if (isFilePresent(configFile)) {
		auto it = configFiles.find(configFile);
		it->second.addToSection(sectionName, valueName, value);
	}
}