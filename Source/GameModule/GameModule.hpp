#pragma once
#include "BaseModule/BaseModule.hpp"
#include "UISystem/UIScreen.hpp"
#include "Screens.hpp"
#include "PlayerCharacter.hpp"
#include "LevelHandlingModule/LevelHandlingModule.hpp"

/*
* This is a general manger class. Holder of all modules. You can access it from any part of the game
*/

class GameModule : public BaseModule
{
public:
	bool initialize() override;

	void run();

	void terminate() override;

	void setCurrentScreen(const Screens& newScreen);

private:
	sf::RenderWindow window;

	std::unordered_map<Screens, std::shared_ptr<UIScreen>> screens;

	Screens currentScreen = Screens::MAIN_MENU;

	float timeCounter = 0.0f;
	int32_t currentStage = 0;

	int32_t gameTime;

	void checkTimeCounter();

	PlayerCharacter player;
	 
	LevelId currentLevel;
};
