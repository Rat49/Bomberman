#include "TestModule.hpp"
#include "TestBase.hpp"
#include "Common/Logs.hpp"
#include <iostream>


TestModule::TestModule()
{
	const int64_t ProposedMaxTestNum = 16;
	m_tests.reserve(ProposedMaxTestNum);

	// for now let's just avoid using tests in release
#ifndef FINAL
	isTestModuleEnabled = true; 
#else
	isTestModuleEnabled = false;
#endif
}

TestModule::~TestModule()
{
}

void TestModule::addTest(const std::shared_ptr<TestBase>& testRunner)
{
	m_tests.insert(m_tests.end(), testRunner);
}

void TestModule::removeTest(const std::shared_ptr<TestBase>& testRunner)
{
	const auto it = std::find(m_tests.begin(), m_tests.end(), testRunner);
	if (it != m_tests.end())
	{
		m_tests.erase(it);
	}
}

void TestModule::run()
{
	for(const auto& test : m_tests)
	{
		LOG("Test " + test->getName() + " started");

		test->setup();
		test->run();

		LOG("Test " + test->getName() + " complete");
	}
}

void TestModule::update(float deltaTime)
{
	for (const auto& test : m_tests)
	{
		test->update(deltaTime);
	}
}
