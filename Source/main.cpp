#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "EventSystem/EventSystem.hpp"
#include <iostream>

// callback function to be called when the window is closed
void onWindowClosedEvent() {
	std::cout << "The window is closed!" << std::endl;
}

void GameLoop()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // get the EventSystem instance
    EventSystem& eventSystem = EventSystem::getInstance();

    // register a new event
    int32_t  windowClosedEventID = eventSystem.registerEvent();

    // subscribe to the window closed event
    eventSystem.subscribe(windowClosedEventID, onWindowClosedEvent);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // emit the window closed event
                eventSystem.emit(windowClosedEventID);

                // unsubscribe from the event
                eventSystem.unsubscribe(windowClosedEventID, onWindowClosedEvent);

                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}

int WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nShowCmd*/)
{
    if (AllocConsole())
    {
        FILE* StreamOut = nullptr;
        FILE* StreamIn = nullptr;
        freopen_s(&StreamOut, "CONOUT$", "wt", stdout);
        freopen_s(&StreamIn, "CONIN$", "rt", stdin);
        SetConsoleTitle("Debug Console");
        std::ios::sync_with_stdio(1);
    }

    GameLoop();

    return 0;
}
