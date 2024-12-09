#include "TestRegisty.hpp"
#include "Common/Logs.hpp"
#include "TestModule/InputModuleTest.hpp"
#include "TestModule/UICheckboxTest.hpp"

std::shared_ptr<TestBase> TestRegisty::createTestByName(const std::string& testName)
{
	auto it = m_tests.find(testName);
	if (it != m_tests.end())
	{
		return it->second();
	}
	LOG("Test [$] does not exist", testName);
	return nullptr;
}