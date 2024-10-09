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

	enum ConfigFileType {
		TEMPORARY = 1,
		PERMANENT = 0
	};

	struct ConfigFileData {
		ConfigFileType isTemporary;
		std::string path;
		std::unordered_map<std::string, std::unordered_map<std::string, std::string>> sections;
	};

	void printConfigFile(const ConfigFileName& fileName) const;

	const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& getConfigFile(const ConfigFileName& configFile) const;

	const std::unordered_map<std::string, std::string>& getConfigFileSection(const ConfigFileName& configFile, const std::string& section) const;

	std::unordered_map<ConfigFileName, ConfigFileData> configFiles = {
		{File1, {TEMPORARY, "Data/Config/config.ini"}},
		{File2, {TEMPORARY, "Data/Config/config.ini"}},
		{File3, {PERMANENT, "Data/Config/config.ini"}}
	};
};