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
	handle = Modules::Events->subscribe<int32_t, float, std::string>(
		windowCloseEventID,
		std::bind(&WindowClosingTest::onWindowClosedEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));


	// Emit the event to see if it works
	Modules::Events->emit<int32_t, float, std::string>(windowCloseEventID, 42, 3.14f, "Window closed test");

	// Unsubscribe to test if the callback is really removed
	Modules::Events->unsubscribe(windowCloseEventID, handle);

	// Emit the event again to confirm that the callback is not called
	Modules::Events->emit<int32_t, float, std::string>(windowCloseEventID, 42, 3.14f, "Should not trigger");
}

void WindowClosingTest::onWindowClosedEvent(int32_t param1, float param2, const std::string& param3)
{
	std::cout << "The window is closed with params: " << param1 << ", " << param2 << ", " << param3 << std::endl;
	windowClosed = true;
}

void WindowClosingTest::run()
{
	LOG("WindowCloseTest: run()");
}

bool WindowClosingTest::isComplete() const
{
	return windowClosed;
}
