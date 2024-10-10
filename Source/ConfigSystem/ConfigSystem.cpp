#include "ConfigSystem.hpp"
#include <iostream>

void ConfigSystem::addFile(const std::string& configFile, const bool& isPermanent, ConfigFileData& fileData)
{
	fileData = parser.parse(configFile, isPermanent);
	if (isPermanent) {
		configFiles[configFile] = fileData;
	}
}

void ConfigSystem::removeFile(const std::string& configFile)
{
	configFiles.erase(configFile);
}

const bool ConfigSystem::isFilePresent(const std::string& configFile) const
{
	return configFiles.find(configFile) != configFiles.end();
}

const bool ConfigSystem::isSectionPresent(const std::string& configFile, const std::string& sectionName) const
{
	if (isFilePresent(configFile)) {
		auto it = configFiles.find(configFile);
		return it->second.sections.find(sectionName) != it->second.sections.end();
	}
	return false;
}

const bool ConfigSystem::isValuePresent(const std::string& configFile, const std::string& sectionName, const std::string& valueName) const
{
	if (isSectionPresent(configFile, sectionName)) {
		auto it = configFiles.find(configFile);
		auto it2 = it->second.sections.find(sectionName);
		return it2->second.find(valueName) != it2->second.end();
	}
	return false;
}

const std::string& ConfigSystem::getValue(const std::string& configFile, const std::string& sectionName, const std::string& valueName) const
{
	if (isValuePresent(configFile, sectionName, valueName)) {
		auto it = configFiles.find(configFile);
		auto it2 = it->second.sections.find(sectionName);
		return it2->second.find(valueName)->second;
	}
	return "";
}

void ConfigSystem::setValue(const std::string& configFile, const std::string& sectionName, const std::string& valueName, const std::string& value)
{
	if (isFilePresent(configFile)) {
		configFiles[configFile].sections[sectionName][valueName] = value;
	}
}

// I added this function so that temporary files can be removed from map (configFiles)
// In current version temporary files aren't stored in map, but addFiles() copies ConfigFileData when adding to map and that might be bad
void ConfigSystem::deleteTemporaryFiles()
{
	for (auto& configFile : configFiles) {
		if (!configFile.second.isPermanent) {
			configFile.second.sections.clear();
		}
	}
}

void ConfigSystem::printConfigFile(const std::string& fileName) const 
{
	auto it = configFiles.find(fileName);
	if (it != configFiles.end()) {
		for (const auto& section : it->second.sections) {
			std::cout << "[" << section.first << "]\n";
			for (const auto& pair : section.second) {
				std::cout << pair.first << "=" << pair.second << "\n";
			}
		}
	}
}
