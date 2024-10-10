#include "TestModule.hpp"
#include "TestBase.hpp"
#include "EventSystem/EventSystem.hpp"
#include "Common/Modules.hpp"
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
	windowCloseEvent();

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

// Callback function to be called when the window is closed
void onWindowClosedEvent() {
	std::cout << "The window is closed!" << std::endl;
}

// Test function for window close event
void TestModule::windowCloseEvent() 
{
	EventSystem& eventSystem = *Modules::EventSystems;

	int32_t windowClosedEventID = eventSystem.registerEvent();

	// Subscribe to the window closed event
	eventSystem.subscribe(windowClosedEventID, onWindowClosedEvent);

	// Simulate window closing
	eventSystem.emit(windowClosedEventID);
}
