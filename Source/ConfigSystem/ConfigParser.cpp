#include "ConfigParser.hpp"
#include <fstream>
#include <iostream>

bool ConfigParser::isSection(const std::string& line) const
{
    return line.front() == '[' && line.back() == ']';
}

void ConfigParser::parse(ConfigFile& configFile) const
{
    const std::string& fileName = configFile.getName();
    std::ifstream      file(fileName);
    if (!file)
    {
        std::cout << "Can't open file: " << fileName << std::endl;
        return;
    }

    // going through file, placing sections and values inside currentMap
    std::string line, section;

    while (std::getline(file, line))
    {
        const auto commentPos = line.find_first_of(" ;#");
        if (commentPos != std::string::npos)
        {
            line = line.substr(0, commentPos);
        }
        if (!line.empty())
        {
            if (isSection(line))
            {
                section = line.substr(1, line.size() - 2);
            }
            else
            {
                std::size_t equalPos = line.find('=');
                if (equalPos == std::string::npos)
                {
                    std::cout << "Wrong format of config file\n";
                }
                std::string key   = line.substr(0, equalPos);
                std::string value = line.substr(equalPos + 1);
                configFile.addToSection(section, key, value);
            }
        }
    }
}