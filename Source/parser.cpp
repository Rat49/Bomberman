#include "parser.hpp"
#include <fstream>
#include <iostream>

bool Parser::isSection(const std::string& line) 
{
    return line.front() == '[' && line.back() == ']';
}

std::string Parser::removeWhitespace(const std::string& str) 
{
    const auto x = str.find_first_not_of(" \t");    //finds whitespace (space or tab) before relevant characters
    const auto y = str.find_last_not_of(" \t");     //finds whitespace after characters
    return (x == std::string::npos) ? "" : str.substr(x, y - x + 1);
}

void Parser::parse() 
{
    std::ifstream file(m_configFile);
    if (!file) 
    {
        std::cout << "Can't open file: " << m_configFile << std::endl;
        return;
    }

    std::string line, section;

    while (getline(file, line)) {
        std::size_t commentPos = line.find_first_of(";#");
        if (commentPos != std::string::npos)    //remove comments
        {
            line.erase(commentPos);
        }

        line = removeWhitespace(line);

        if (!line.empty()) 
        {
            if (isSection(line)) 
            {
                section = line.substr(1, line.size() - 2);
            }
            else 
            {
                std::size_t equalPos = line.find('=');
                if (equalPos == std::string::npos) {
                    std::cout << "Wrong format of config file\n";
                }
                std::string key = removeWhitespace(line.substr(0, equalPos));
                std::string value = removeWhitespace(line.substr(equalPos + 1));

                m_configData[section][key] = value;
            }
        }
    }
}

void Parser::printMap() 
{
    for (const auto& section : m_configData) 
    {
        std::cout << "[" << section.first << "]\n";
        for (const auto& pair : section.second) 
        {
            std::cout << pair.first << "=" << pair.second << "\n";
        }
    }
}
