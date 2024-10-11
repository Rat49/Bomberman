#include "ConfigSystem.hpp"
#include <iostream>

void ConfigSystem::addFile(ConfigFile& fileData)
{
	parser.parse(fileData);
	if (fileData.getIsPermanent()) {
		configFiles[fileData.getName()] = fileData;
	}
}

void ConfigSystem::removeFile(const std::string& configFile)
{
	configFiles.erase(configFile);
}

bool ConfigSystem::isFilePresent(const std::string& configFile) const
{
	return configFiles.find(configFile) != configFiles.end();
}

bool ConfigSystem::isSectionPresent(const std::string& configFile, const std::string& sectionName) const
{
	if (isFilePresent(configFile)) {
		auto it = configFiles.find(configFile);
		return it->second.isSectionPresent(sectionName);
	}
	return false;
}

bool ConfigSystem::isValuePresent(const std::string& configFile, const std::string& sectionName, const std::string& valueName) const
{
	if (isSectionPresent(configFile, sectionName)) {
		auto it = configFiles.find(configFile);
		auto it2 = it->second.getSection(sectionName);
		return it2.isValuePresent(valueName);
	}
	return false;
}

const ConfigValue& ConfigSystem::getValue(const std::string& configFile, const std::string& sectionName, const std::string& valueName) const
{
	auto it = configFiles.find(configFile);
	auto it2 = it->second.getSection(sectionName);
	return it2.getValue(valueName);
}

void ConfigSystem::setValue(const std::string& configFile, const std::string& sectionName, const std::string& valueName, const std::string& value)
{
	if (isFilePresent(configFile)) {
		auto it = configFiles.find(configFile);
		it->second.addToSection(sectionName, valueName, value);
	}
}