#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#ifndef FINAL

enum TestsMode
{
    RunLast,
    RunDefined
};

class TestBase;
namespace sf
{
class RenderWindow;
}
/*
* Module which allows you to add test of any type and perform them outside of the game.
* Best place to register your test is in your module constructor!
*/
class TestModule
{
public:
    TestModule();
    ~TestModule();

    static void CreateTests();

    // Add your implementation of test
    void addTest(const std::shared_ptr<TestBase>& testRunner);

    // Remove the test if you changed your mind..
    void removeTest(const std::shared_ptr<TestBase>& testRunner);

    // Start all the tests. First will be called setup and then run for each test.
    void run();

    // Tick for all tests
    void update(float deltaTime, sf::RenderWindow* window);

private:
    bool                                   m_isLastTestFinished = false;
    std::vector<int32_t>                   m_testsIDs;
    std::vector<std::shared_ptr<TestBase>> m_tests;
};

#endif
