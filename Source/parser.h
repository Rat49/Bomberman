#pragma once

#include <string>
#include <unordered_map>

bool isSection(const std::string& line);

void parse(const std::string& configFile, std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& data);

void printMap(std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& data);