#include "TestModule.hpp"
#include "TestBase.hpp"
#include "Common/Logs.hpp"
#include "Common/Modules.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "ConfigSystem/ConfigSection.hpp"
#include <iostream>

#ifndef FINAL

namespace
{
	const std::string TEST_MODULE_CONFIG_PATH = "../../Data/Config/TestModule.ini";
}

TestModule::TestModule()
{
	const int64_t ProposedMaxTestNum = 16;
	m_tests.reserve(ProposedMaxTestNum);

	Modules::Config->addFile(TEST_MODULE_CONFIG_PATH);
	const ConfigFile& testModuleConfig = Modules::Config->getFile(TEST_MODULE_CONFIG_PATH);
	const auto& sections = testModuleConfig.getAllSections();
	m_testsMode = testModuleConfig.getSection("TestsMode").getValue("mode").getInt32();
	
	for (const auto& section : sections)
	{
		if (section != "TestsMode" && testModuleConfig.getSection(section).isValuePresent("testID"))
		{
			m_testsIDs.push_back(testModuleConfig.getSection(section).getValue("testID").getInt32());
		}
	}
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
	
	for ( auto id : m_testsIDs)
	{
		if (id >= 0 && id < m_tests.size())
		{
			m_predefinedTests.push_back(m_tests[id]);
		}
	}

	switch (m_testsMode) 
	{
	case TestsMode::RunLast:
		if (!m_tests.empty())
		{
			const auto& lastTest = m_tests.back();
			LOG("Test " + lastTest->getName() + " started");
			lastTest->setup();
			lastTest->run();
		}
		break;
	case TestsMode::RunDefined:
		for (const auto& test : m_predefinedTests)
		{
			LOG("Test " + test->getName() + " started");
			test->setup();
			test->run();
		}
		break;
	default:
		for (const auto& test : m_tests)
		{
			LOG("Test " + test->getName() + " started");
			test->setup();
			test->run();
		}
		break;
	}
}

void TestModule::update(float deltaTime, sf::RenderWindow* window)
{
	if (m_tests.empty())
	{
		return;
	}

	std::vector<std::shared_ptr<TestBase>>::iterator predefined_it = m_predefinedTests.begin();
	std::vector<std::shared_ptr<TestBase>>::iterator tests_it = m_tests.begin();
	switch (m_testsMode)
	{
	case TestsMode::RunLast:
		if (!m_tests.empty() && !m_isLastTestFinished)
		{
			const auto& lastTest = m_tests.back();
			lastTest->update(deltaTime, window);
			if (lastTest->isComplete())
			{
				LOG("Test " + lastTest->getName() + " complete");
				m_isLastTestFinished = true;
				m_tests.pop_back();
			}
		}
		break;
	case TestsMode::RunDefined:
		while (predefined_it != m_predefinedTests.end())
		{
			(*predefined_it)->update(deltaTime, window);

			if ((*predefined_it)->isComplete())
			{
				LOG("Test " + (*predefined_it)->getName() + " complete");
				predefined_it = m_predefinedTests.erase(predefined_it);
			}
			else
			{
				++predefined_it;
			}
		}
		break;
	default:
		while (tests_it != m_tests.end())
		{
			(*tests_it)->update(deltaTime, window);

			if ((*tests_it)->isComplete())
			{
				LOG("Test " + (*tests_it)->getName() + " complete");
				tests_it = m_tests.erase(tests_it);
			}
			else
			{
				++tests_it;
			}
		}
		break;
	}
}

#endif
