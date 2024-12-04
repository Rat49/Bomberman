#include "TestRegisty.hpp"
#include "Common/Logs.hpp"
#include "TestFactoryCreator.hpp"
#include "TestModule/InputModuleTest.hpp"
#include "TestModule/UICheckboxTest.hpp"

bool TestRegisty::registerFactory(const std::string& testName, const std::shared_ptr<TestFactory>& testFactory)
{
	auto it = m_factories.find(testName);
	if (it != m_factories.end())
	{
		LOG("Test factory [$] already registered", testName);
		return false;
	}
	m_factories.emplace(testName, testFactory);
	m_lastFactory = testFactory;
	return true;
}

std::shared_ptr<TestBase> TestRegisty::createTestByName(const std::string& testName)
{
	auto it = m_factories.find(testName);
	if (it == m_factories.end())
	{
		LOG("Test [$] does not exist", testName);
		return nullptr;
	}
	return it->second->createTest();
}