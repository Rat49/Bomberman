#pragma once
#include "BaseModule/BaseModule.hpp"
#include "UISystem/UIScreen.hpp"
#include "GameModule/LevelGenerator.hpp"
#include "Screens.hpp"
#include "PlayerCharacter.hpp"
#include "LevelHandlingModule/LevelHandlingModule.hpp"
#include "Boosters/BoosterComponent.hpp"

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
	void addBooster(std::shared_ptr<BoosterComponent> newBooster);

	void removeAllBoosters();

	void updateBoosters();

private:
	sf::RenderWindow window;

	std::unordered_map<Screens, std::shared_ptr<UIScreen>> screens;

	std::map<int32_t, std::shared_ptr<BoosterComponent>> m_boosters;

	Screens currentScreen = Screens::MAIN_MENU;

	float timeCounter = 0.0f;
	int32_t currentStage = 0;

	int32_t gameTime;

	void checkTimeCounter();

	PlayerCharacter player;

	std::unique_ptr<LevelGenerator> levelGenerator;
	 
	LevelId currentLevel;

	bool resized = false;
};
