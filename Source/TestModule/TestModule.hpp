#pragma once
#include <vector>
#include <memory>

#ifndef FINAL


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
	// Remove the test if you changed your mind..
	void removeTest(const std::shared_ptr<TestBase>& testRunner);

	// Start all the tests. First will be called setup and then run for each test.
	void run();

	// Tick for all tests
	void update(float deltaTime, sf::RenderWindow* window);

private:
	std::vector<std::shared_ptr<TestBase>> m_tests;
};

#endif
