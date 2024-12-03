#pragma once
#include <vector>
#include <memory>
#include <map>
#include <string>

#ifndef FINAL

enum TestsMode
{
	RunLast,
	RunDefined
};

class TestBase;
namespace sf {
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

	static void CreateAllTests();

	// Add your implementation of test
	void addTest(const std::shared_ptr<TestBase>& testRunner);

	void TestModule::addTest(std::pair<std::string, std::shared_ptr<TestBase>> newTest);

	// Remove the test if you changed your mind..
	void removeTest(const std::shared_ptr<TestBase>& testRunner);

	// Start all the tests. First will be called setup and then run for each test.
	void run();

	// Tick for all tests
	void update(float deltaTime, sf::RenderWindow* window);

private:
	bool m_isLastTestFinished = false;
	int32_t m_testsMode;
	std::vector<int32_t>m_testsIDs;
 	std::vector<std::shared_ptr<TestBase>> m_tests;
	std::vector<std::shared_ptr<TestBase>> m_predefinedTests;

	// store tests in a map, that way testName can be used as a key
	// ,that way id wont be use but a test name in .ini file
	std::map<std::string, std::shared_ptr<TestBase>> m_testsMap;
};

#endif
