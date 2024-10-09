#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "EventSystem/EventSystem.hpp"
#include <iostream>

void GameLoop()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
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
