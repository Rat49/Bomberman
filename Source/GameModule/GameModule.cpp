#include "GameModule/GameModule.hpp"
#include "Common/Modules.hpp"
#include "TestModule/TestModule.hpp"
#include "InputModule/InputModule.hpp"
#include "EventSystem/EventSystem.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>


using Time = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<float, std::micro>;

void GameModule::run()
{
#ifndef FINAL
	Modules::Tests->run();
#endif

    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    Time::time_point currentTime;
    Time::time_point prevTime = Time::now();
    float deltaTime = 0.0f;


    while (window.isOpen())
    {
        // handling delta time
        currentTime = Time::now();
        deltaTime = std::chrono::duration_cast<Duration>(currentTime - prevTime).count();
        prevTime = currentTime;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

#ifndef FINAL
        Modules::Tests->update(deltaTime, &window);
#endif
        Modules::update(deltaTime, &window);

        window.clear();
        window.draw(shape);
        window.display();
    }
}

void GameModule::terminate()
{
}
