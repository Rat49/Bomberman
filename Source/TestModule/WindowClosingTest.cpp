#include "TestModule/WindowClosingTest.hpp"
#include "Common/Logs.hpp"
#include "Common/Modules.hpp"
#include "EventSystem/EventSystem.hpp"
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

    auto params = new WindowCloseParams{42, 3.14f, "Window closed test"};

    // Subscribe the event to a callback that will close the window
    handle = Modules::Events->subscribe(windowCloseEventID,
                                        [this](void* data)
                                        {
                                            auto params = static_cast<WindowCloseParams*>(data);
                                            this->onWindowClosedEvent(params->param1, params->param2, params->param3);
                                        });

    // Emit the event to see if it works
    Modules::Events->emit(windowCloseEventID, params);

    // Unsubscribe to test if the callback is really removed
    Modules::Events->unsubscribe(windowCloseEventID, handle);

    // Emit the event again to confirm that the callback is not called
    Modules::Events->emit(windowCloseEventID, params);
}

void WindowClosingTest::onWindowClosedEvent(int32_t param1, float param2, const std::string& param3)
{
    std::string message = "The window is closed with params: " + std::to_string(param1) + ", " +
                          std::to_string(param2) + ", " + param3;
    LOG(message);
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
