#pragma once
#include "ConfigValue.hpp"
#include <unordered_map>

class ConfigSection
{
public:
	const ConfigValue& getValue(const std::string& name) const;

	void setValue(const std::string& name, const ConfigValue& value);

	bool isValuePresent(const std::string& valueName) const;

	bool areValuesPresent(const std::vector<std::string>& keys) const;

	bool isEmpty() const;

private:
	std::unordered_map<std::string, ConfigValue> m_values;
};