#pragma once
#include "TestBase.hpp"
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

class TestRegisty
{
public:
    template <typename T>
    bool registerTest(const std::string& testName);

    bool initialize();

    std::shared_ptr<TestBase> createTestByName(const std::string& testName);

    const std::unordered_map<std::string, std::function<std::shared_ptr<TestBase>()>>& getTests() const
    {
        return m_tests;
    }

    const std::function<std::shared_ptr<TestBase>()>& getLastRegisteredTest() const
    {
        return m_lastTest;
    }

private:
    std::function<std::shared_ptr<TestBase>()> m_lastTest;

    std::unordered_map<std::string, std::function<std::shared_ptr<TestBase>()>> m_tests;
};


template <typename T>
bool TestRegisty::registerTest(const std::string& testName)
{
    auto it = m_tests.find(testName);
    if (it != m_tests.end())
    {
        LOG("Test test [$] already registered", testName);
        return false;
    }

    std::function<std::shared_ptr<TestBase>()> newTestFunction = []() -> std::shared_ptr<TestBase>
    { return std::make_shared<T>(); };

    m_lastTest = newTestFunction;

    m_tests.emplace(testName, std::move(newTestFunction));

    return true;
}