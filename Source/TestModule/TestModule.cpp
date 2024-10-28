#include "TestModule.hpp"
#include "TestBase.hpp"
#include "Common/Logs.hpp"
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
		LOG("Test " + test->getName() + " started");

		test->setup();
		test->run();
	}
}

void TestModule::update(float deltaTime, sf::RenderWindow* window)
{
	if (m_tests.empty())
	{
		return;
	}

	std::vector<std::shared_ptr<TestBase>>::iterator it = m_tests.begin();
	while(it != m_tests.end())
	{
		(*it)->update(deltaTime, window);

		if ((*it)->isComplete())
		{
			LOG("Test " + (*it)->getName() + " complete");
			it = m_tests.erase(it);
		}
		else
		{
			++it;
		}
	}
}

#endif
