#include "ConfigSection.hpp"

const ConfigValue& ConfigSection::getValue(const std::string& name) const
{
	auto it = m_values.find(name);
	if (it != m_values.end()) {
		return it->second;
	}
	else {
		static const ConfigValue defaultValue;
		return defaultValue;
	}
}

void ConfigSection::setValue(const std::string& name, const ConfigValue& value)
{
	m_values[name] = value;
}

bool ConfigSection::isValuePresent(const std::string& valueName) const
{
	return m_values.find(valueName) != m_values.end();
}

bool ConfigSection::areValuesPresent(const std::vector<std::string>& keys) const
{
	for (const std::string& key : keys) {
		if (!isValuePresent(key)) 
			return false;
	}
	return true;
}

bool ConfigSection::isEmpty() const
{
	return m_values.empty();
}
