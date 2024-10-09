#include "FileData.hpp"
#include <iostream>

void FileData::printConfigFile(const ConfigFileName& fileName) const {
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

const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& FileData::getConfigFile(const ConfigFileName& configFile) const {
	auto it = configFiles.find(configFile);
	if (it != configFiles.end())
		return it->second.sections;
	return {};
}

const std::unordered_map<std::string, std::string>& FileData::getConfigFileSection(const ConfigFileName& configFile, const std::string& section) const
{
	auto it = configFiles.find(configFile);
	if (it != configFiles.end()) {
		auto it2 = (it->second).sections.find(section);
		if (it2 != it->second.sections.end())
			return it2->second;
	}
	return {};
}
