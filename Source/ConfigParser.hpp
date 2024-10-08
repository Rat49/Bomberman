#ifndef SFML_PARSER_HPP
#define SFML_PARSER_HPP

#include <string>
#include <unordered_map>

class ConfigParser 
{
public:
	ConfigParser(const std::string& configFile) : m_configFile(configFile)
	{}

	void parse();

	void printMap();

	const std::unordered_map<std::string, std::string>& getSectionValues(const std::string& section) const;

private:
	bool isSection(const std::string& line);

	std::string removeWhitespace(const std::string& str);

	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_configData;

	std::string m_configFile;
};

#endif // SFML_PARSER_HPP