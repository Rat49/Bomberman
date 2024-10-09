#pragma once

#include <string>
#include <unordered_map>

class FileData {
public:
	enum ConfigFileName {
		File1,
		File2,
		File3
	};

	struct ConfigFileData {
		bool isTemporary;
		std::string path;
		std::unordered_map<std::string, std::unordered_map<std::string, std::string>> sections;
	};

	void printConfigFile(const ConfigFileName& fileName) const;

	const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& getConfigFile(const ConfigFileName& configFile) const;

	const std::unordered_map<std::string, std::string>& getConfigFileSection(const ConfigFileName& configFile, const std::string& section) const;

	std::unordered_map<ConfigFileName, ConfigFileData> configFiles = {
		{File1, {false, "Data/Config/config.ini"}},
		{File2, {false, "Data/Config/config.ini"}},
		{File3, {true, "Data/Config/config.ini"}}
	};
};