#include "GameModule/GameModule.hpp"
#include "Common/Modules.hpp"
#include "TestModule/TestModule.hpp"
#include "InputModule/InputModule.hpp"
#include "EventSystem/EventSystem.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "HUD.hpp"
#include "MainMenu.hpp"
#include "StageScreen.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>

namespace {
	const std::string& PATH_WINDOW_INFO = "../../Data/Config/windowInfo.ini";
	const std::string& PATH_HUD = "../../Data/Config/HUD.ini";
	const std::string& PATH_MAIN_MENU = "../../Data/Config/mainMenu.ini";
	const std::string& PATH_STAGE = "../../Data/Config/stageScreen.ini";
	const std::string& WINDOW = "Window";
	const std::string& WIDTH = "width";
	const std::string& HEIGHT = "height";
	const std::string& TITLE = "title";
	const std::string& FONT = "font";
	const std::string& GAME_TIME = "gameTime";
	const std::string& STAGE = "stage";

	const sf::Color& GREY = sf::Color(189, 190, 189);
	const sf::Color& BLACK = sf::Color::Black;
}

using Time = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<float, std::micro>;

bool GameModule::initialize() {

	// Reading config file
	Modules::Config->addFile(PATH_WINDOW_INFO);
	Modules::Config->addFile(PATH_HUD);
	Modules::Config->addFile(PATH_MAIN_MENU);
	Modules::Config->addFile(PATH_STAGE);
	const ConfigFile& windowInfo = Modules::Config->getFile(PATH_WINDOW_INFO);

	if (!windowInfo.isSectionPresent(WINDOW))
		return false;

	const auto& windowSection = windowInfo.getSection(WINDOW);

	if (!windowSection.areValuesPresent({ WIDTH, HEIGHT, FONT, TITLE, GAME_TIME, STAGE }))
		return false;

	int32_t width = windowSection.getValue(WIDTH).getInt32();
	int32_t height = windowSection.getValue(HEIGHT).getInt32();
	const std::string& title = windowSection.getValue(TITLE).getString();
	const std::string& font = windowSection.getValue(FONT).getString();
	gameTime = windowSection.getValue(GAME_TIME).getInt32();
	currentStage = windowSection.getValue(STAGE).getInt32();

	// Creating Window and HUD
	window.create(sf::VideoMode(width, height), title);

	// Creating all screens
	screens[Screens::LEVEL] = std::make_shared<HUD>(&window, font, PATH_HUD);
	screens[Screens::MAIN_MENU] = std::make_shared<MainMenu>(&window, font, PATH_MAIN_MENU);
	screens[Screens::STAGE] = std::make_shared<StageScreen>(&window, font, PATH_STAGE);

	auto screenStage = (std::dynamic_pointer_cast<StageScreen>(screens[Screens::STAGE]));
	screenStage->setStage(currentStage);
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

    while (window.isOpen())
    {
        // handling delta time
        currentTime = Time::now();
        deltaTime = std::chrono::duration_cast<Duration>(currentTime - prevTime).count();
        prevTime = currentTime;

        sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				Modules::UI->setViewportSize((float)(screens[currentScreen]->getWindow()->getSize().x), (float)(screens[currentScreen]->getWindow()->getSize().y));
				[[fallthrough]];

			case sf::Event::MouseMoved:
			case sf::Event::MouseButtonPressed:
			case sf::Event::MouseButtonReleased:
				screens[currentScreen]->handleEvent(event);
				break;

			}
		}

		timeCounter += deltaTime;

		checkTimeCounter();

#ifndef FINAL
        Modules::Tests->update(deltaTime, &window);
#endif
        Modules::update(deltaTime, &window);

		window.clear(screens[currentScreen]->getBackgroundColor());
		screens[currentScreen]->draw(window, sf::RenderStates::Default);
        window.display();
    }
}

void GameModule::terminate()
{
}

void GameModule::setCurrentScreen(const Screens& newScreen)
{
	currentScreen = newScreen;
	timeCounter = 0.0f;
}

void GameModule::checkTimeCounter()
{
	switch (currentScreen)
	{
	case Screens::LEVEL:
		// Checking if one second has passed for updating Time label (delta time is in microseconds)
		if (timeCounter >= 1000000) {
			timeCounter = 0.0f;
			gameTime--;

			auto hud = (std::dynamic_pointer_cast<HUD>(screens[currentScreen]));
			hud->setTime(std::to_string(gameTime));
		}
		break;
	case Screens::STAGE:
		// Checking if 2 seconds has passed for updating Screen
		if (timeCounter >= 2000000) {
			setCurrentScreen(Screens::LEVEL);
		}
		break;
	}
}
