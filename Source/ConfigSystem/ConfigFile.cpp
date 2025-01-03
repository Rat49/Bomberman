#include "ConfigFile.hpp"
#include <SaveSystem/FileReader.hpp>
#include <fstream>

bool ConfigFile::open()
{
    FileReader reader;
    if (!reader.open(m_name))
    {
        return false;
    }
    return true;
}

const std::vector<std::string> ConfigFile::getAllSections() const
{
    std::vector<std::string> res;
    for (const auto& it : m_sections)
    {
        res.push_back(it.first);
    }
    return res;
}

const ConfigSection& ConfigFile::getSection(const std::string& name) const
{
    auto it = m_sections.find(name);
    if (it != m_sections.end())
    {
        return it->second;
    }
    else
    {
        static const ConfigSection defaultValue;
        return defaultValue;
    }
}

void ConfigFile::setSection(const std::string& name, const ConfigSection& section)
{
    m_sections[name] = section;
}

void ConfigFile::addToSection(const std::string& name, const std::string& valueName, const std::string& value)
{
    m_sections[name].setValue(valueName, value);
}

bool ConfigFile::isSectionPresent(const std::string& sectionName) const
{
    return m_sections.find(sectionName) != m_sections.end();
}
