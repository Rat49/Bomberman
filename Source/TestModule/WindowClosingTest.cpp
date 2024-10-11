#include "TestModule/WindowClosingTest.hpp"
#include "Common/Modules.hpp"
#include "EventSystem/EventSystem.hpp"
#include "Common/Logs.hpp"
#include <iostream>

const std::string& WindowClosingTest::getName() const
{
	return Name;
}

void WindowClosingTest::setup()
{
	LOG("WindowCloseTest: setup()");

	// Register the window close event
	windowCloseEventID = Modules::Events->registerEvent();

	// Subscribe the event to a callback that will close the window
	Modules::Events->subscribe(windowCloseEventID, [this]() {
		onWindowClosedEvent();
		windowClosed = true;
		});
}

void WindowClosingTest::onWindowClosedEvent()
{
	std::cout << "The window is closed!" << std::endl;
}

void WindowClosingTest::run()
{
	LOG("WindowCloseTest: run()");
}

bool WindowClosingTest::isComplete() const
{
	return windowClosed;
}
