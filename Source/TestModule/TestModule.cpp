#include "TestModule.hpp"
#include "Common/Logs.hpp"
#include "Common/Modules.hpp"
#include "ConfigSystem/ConfigSection.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "TestBase.hpp"
#include "TestModule/TestRegisty.hpp"
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
    CreateTests();

    for (const auto& test : m_tests)
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

    std::vector<std::shared_ptr<TestBase>>::iterator tests_it = m_tests.begin();

    while (tests_it != m_tests.end())
    {
        TestBase* test = tests_it->get();
        test->update(deltaTime, window);
        if (test->isComplete())
        {
            LOG("Test " + test->getName() + " complete");
            tests_it = m_tests.erase(tests_it);
        }
        else
        {
            ++tests_it;
        }
    }
}

void TestModule::CreateTests()
{
    Modules::Config->addFile(TEST_MODULE_CONFIG_PATH);
    const ConfigFile&            testModuleConfig = Modules::Config->getFile(TEST_MODULE_CONFIG_PATH);
    const auto&                  sections         = testModuleConfig.getAllSections();
    int32_t                      testsMode   = testModuleConfig.getSection("TestsMode").getValue("mode").getInt32();
    std::unique_ptr<TestRegisty> testRegisty = std::make_unique<TestRegisty>();

    if (!testRegisty->initialize())
    {
        // LOG("Some of the tests have failed to initialize");
        return;
    }

    switch (testsMode)
    {
        case TestsMode::RunLast:
            Modules::Tests->addTest(testRegisty->getLastRegisteredTest()());
            break;
        case TestsMode::RunDefined:
            for (const auto& section : sections)
            {
                if (section != "TestsMode" && testModuleConfig.getSection(section).isValuePresent("testName"))
                {
                    Modules::Tests->addTest(testRegisty->createTestByName(
                        testModuleConfig.getSection(section).getValue("testName").getString()));
                }
            }
            break;
        default:
            for (const auto& el : testRegisty->getTests())
            {
                Modules::Tests->addTest(el.second());
            }
            break;
    }
}

#endif
