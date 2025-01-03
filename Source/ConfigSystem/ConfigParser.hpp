#pragma once

#include "ConfigFile.hpp"
#include <string>
#include <unordered_map>

class ConfigParser
{
public:
    void parse(ConfigFile& configFile) const;

private:
    bool isSection(const std::string& line) const;
};