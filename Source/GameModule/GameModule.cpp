#include "GameModule/GameModule.hpp"
#include "Common/Modules.hpp"
#include "TestModule/TestModule.hpp"
#include "InputModule/InputModule.hpp"
#include "EventSystem/EventSystem.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>

namespace {
	const std::string& PATH_WINDOW_INFO = "../../Data/Config/windowInfo.ini";
	const std::string& WINDOW = "Window";
	const std::string& WIDTH = "width";
	const std::string& HEIGHT = "height";
	const std::string& TITLE = "title";
	const std::string& FONT = "font";
	const sf::Color& GREY = sf::Color(189, 190, 189);
}

using Time = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<float, std::micro>;

bool GameModule::initialize() {

	// Reading config file
	Modules::Config->addFile(PATH_WINDOW_INFO);
	const ConfigFile& windowInfo = Modules::Config->getFile(PATH_WINDOW_INFO);

	if (!windowInfo.isSectionPresent(WINDOW))
		return false;

	const auto& windowSection = windowInfo.getSection(WINDOW);

	if (!windowSection.areValuesPresent({ WIDTH, HEIGHT, FONT, TITLE }))
		return false;

	int32_t width = windowSection.getValue(WIDTH).getInt32();
	int32_t height = windowSection.getValue(HEIGHT).getInt32();
	const std::string& title = windowSection.getValue(TITLE).getString();
	const std::string& font = windowSection.getValue(FONT).getString();

	// Creating Window and HUD
	window.create(sf::VideoMode(width, height), title);
	hud = std::make_unique<HUD>(&window, font);

	return true;
}

void GameModule::run()
{
#ifndef FINAL
	Modules::Tests->run();
#endif

    Time::time_point currentTime;
    Time::time_point prevTime = Time::now();
    float deltaTime = 0.0f;
	int32_t gameTime = 200;
	float timeCounter = 0.0f;

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

		timeCounter += deltaTime;

		// Checking if one second has passed for updating Time label (delta time is in microseconds)
		if (timeCounter >= 1000000) {
			timeCounter = 0.f;
			gameTime--;

			hud->setTime(std::to_string(gameTime));
		}

#ifndef FINAL
        Modules::Tests->update(deltaTime, &window);
#endif
        Modules::update(deltaTime, &window);


        window.clear(GREY);
		hud->draw(window, sf::RenderStates::Default);
        window.display();
    }
}

void GameModule::terminate()
{
}
