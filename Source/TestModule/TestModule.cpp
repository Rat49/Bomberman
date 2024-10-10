#include "TestModule.hpp"
#include "TestBase.hpp"
#include <iostream>

#ifndef FINAL

TestModule::TestModule()
{
	const int64_t ProposedMaxTestNum = 16;
	m_tests.reserve(ProposedMaxTestNum);
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
	CreateAllTests();

	for(const auto& test : m_tests)
	{
		std::cout << "Test " << test->getName() << " started\n";

		test->setup();
		test->run();

		std::cout << "Test " << test->getName() << " complete\n";
	}
}

void TestModule::update(float deltaTime)
{
	for (const auto& test : m_tests)
	{
		test->update(deltaTime);
	}
}

#endif
