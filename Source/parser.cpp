#include "parser.h"
#include <fstream>
#include <iostream>

bool isSection(const std::string& line) {
    return line.front() == '[' && line.back() == ']';
}

std::string removeWhitespace(const std::string& str) {
    const auto x = str.find_first_not_of(" \t");    //finds whitespace (space or tab) before relevant characters
    const auto y = str.find_last_not_of(" \t");     //finds whitespace after characters
    return (x == std::string::npos) ? "" : str.substr(x, y - x + 1);
}

void parse(const std::string& configFile, std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& data) {
    std::ifstream file(configFile);
    if (!file) {
        std::cout << "Can't open file: " << configFile << std::endl;
        return;
    }

    std::string line, section;

    while (getline(file, line)) {
        std::size_t commentPos = line.find_first_of(";#");
        if (commentPos != std::string::npos) {  //remove comments
            line.erase(commentPos);
        }

        line = removeWhitespace(line);

        if (!line.empty()) {
            if (isSection(line)) {
                section = line.substr(1, line.size() - 2);
            }
            else {
                std::size_t equalPos = line.find('=');
                if (equalPos == std::string::npos) {
                    std::cout << "Wrong format of config file\n";
                }
                std::string key = removeWhitespace(line.substr(0, equalPos));
                std::string value = removeWhitespace(line.substr(equalPos + 1));

                data[section][key] = value;
            }
        }
    }
}

void printMap(std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& configData) {
    for (const auto& section : configData) {
        std::cout << "[" << section.first << "]\n";
        for (const auto& pair : section.second) {
            std::cout << pair.first << "=" << pair.second << "\n";
        }
    }
}
