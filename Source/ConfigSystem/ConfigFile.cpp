#include "ConfigFile.hpp"
#include <fstream>

bool ConfigFile::open()
{
	std::ifstream file(m_name);
	if (!file) return false;
	return true;
}

const ConfigSection& ConfigFile::getSection(const std::string& name) const
{
	auto it = m_sections.find(name);
	return it->second;
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
