#pragma once
#include "ConfigSection.hpp"

class ConfigFile
{
public:
    ConfigFile(const std::string& name = "") : m_name(name)
    {
    }

    const std::string& getName() const
    {
        return m_name;
    }

    bool open();

    const std::vector<std::string> getAllSections() const;

    const ConfigSection& getSection(const std::string& name) const;

    void setSection(const std::string& name, const ConfigSection& section);

    void addToSection(const std::string& name, const std::string& valueName, const std::string& value);

    bool isSectionPresent(const std::string& sectionName) const;

private:
    std::unordered_map<std::string, ConfigSection> m_sections;

    std::string m_name;
};