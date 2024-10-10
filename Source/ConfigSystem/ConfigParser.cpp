#include "ConfigParser.hpp"
#include <fstream>
#include <iostream>

const bool ConfigParser::isSection(const std::string& line) const 
{
	return line.front() == '[' && line.back() == ']';
}

ConfigFileData ConfigParser::parse(const std::string& configFile, const bool& isPermanent) const
{
	// finding file and checking if exists
	std::ifstream file(configFile);
	if (!file)
	{
		std::cout << "Can't open file: " << configFile << std::endl;
		return ConfigFileData(isPermanent);
	}

	// going through file, placing sections and values inside currentMap 
	std::string line, section;
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> currentMap;

	while (std::getline(file, line)) {
		const auto commentPos = line.find_first_of(" ;#");
		if (commentPos != std::string::npos) {
			line = line.substr(0, commentPos);
		}
		if (!line.empty()) {
			if (isSection(line)) {
				section = line.substr(1, line.size() - 2);
			}
			else {
				std::size_t equalPos = line.find('=');
				if (equalPos == std::string::npos) {
					std::cout << "Wrong format of config file\n";
				}
				std::string key = line.substr(0, equalPos);
				std::string value = line.substr(equalPos + 1);

				currentMap[section][key] = value;
			}
		}
	}
	return ConfigFileData(isPermanent, currentMap);
}