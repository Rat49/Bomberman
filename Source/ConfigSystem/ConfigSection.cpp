#include "ConfigSection.hpp"

const ConfigValue& ConfigSection::getValue(const std::string& name) const
{
	auto it = m_values.find(name);
	return it->second;
}

void ConfigSection::setValue(const std::string& name, const ConfigValue& value)
{
	m_values[name] = value;
}

bool ConfigSection::isValuePresent(const std::string& valueName) const
{
	return m_values.find(valueName) != m_values.end();
}
