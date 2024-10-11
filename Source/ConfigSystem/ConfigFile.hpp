#pragma once
#include "ConfigSection.hpp"

class ConfigFile
{
public:
	ConfigFile(const std::string& name="", bool isPermanent=false) : m_name(name), m_isPermanent(isPermanent) { }

	const std::string& getName() const { return m_name; }

	bool getIsPermanent() const { return m_isPermanent; }

	bool open();

	const ConfigSection& getSection(const std::string& name) const;

	void setSection(const std::string& name, const ConfigSection& section);

	void addToSection(const std::string& name, const std::string& valueName, const std::string& value);

	bool isSectionPresent(const std::string& sectionName) const;

private:
	std::unordered_map <std::string, ConfigSection> m_sections;

	std::string m_name;

	bool m_isPermanent;
};