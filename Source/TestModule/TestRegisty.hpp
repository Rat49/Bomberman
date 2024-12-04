#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "TestFactory.hpp"

class TestRegisty
{
public:
	bool registerFactory(const std::string& testName, const std::shared_ptr<TestFactory>& testFactory);

	bool initialize();

	std::shared_ptr<TestBase> createTestByName(const std::string& testName);

	const std::unordered_map<std::string, std::shared_ptr<TestFactory>>& getFactories() const { return m_factories; }

	const std::shared_ptr<TestFactory>& getLastRegisteredFactory() const { return m_lastFactory; }

private:
	std::unordered_map<std::string, std::shared_ptr<TestFactory>> m_factories;
	std::shared_ptr <TestFactory> m_lastFactory;
};

