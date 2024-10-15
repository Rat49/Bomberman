#pragma once
#include <string>
#include <iostream>

class ConfigValue
{
public:
	ConfigValue(const std::string& value = "") : m_value(value) {}

	const std::string& getString() const { return m_value; }

	int32_t getInt32() const { return std::stoi(m_value); }

	int64_t getInt64() const { return std::stoll(m_value); }

	float getFloat() const { return std::stof(m_value); }

	bool getBool() const { return m_value == "true"; }

	void setString(const std::string& value) { m_value = value; }

	void setInt32(int32_t value) { m_value = std::to_string(value); }

	void setInt64(int64_t value) { m_value = std::to_string(value); }

	void setFloat(float value) { m_value = std::to_string(value); }

	void setBool(bool value) { m_value = value ? "true" : "false"; }

private:
	std::string m_value;
};