#pragma once
#include "BaseModule/BaseModule.hpp"
#include "UISystem/UIScreen.hpp"
#include "GameModule/LevelGenerator.hpp"
#include "UIConstants.hpp"
#include "PlayerCharacter.hpp"
#include "LevelHandlingModule/LevelHandlingModule.hpp"
#include "LevelGeneratorManager.hpp"
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

	void setIsPaused(bool newPaused) { isPaused = newPaused; }

	bool getIsPaused() const { return isPaused; }

private:

	void addBooster(std::shared_ptr<BoosterComponent> newBooster);

	void removeAllBoosters();

	void updateBoosters();

	void checkTimeCounter();

private:

	sf::RenderWindow window;

	PlayerCharacter player;
	
	std::unique_ptr<LevelGeneratorManager> levelGeneratorManager;
	
	std::unordered_map<Screens, std::shared_ptr<UIScreen>> screens;

	std::map<int32_t, std::shared_ptr<BoosterComponent>> m_boosters;

	Screens currentScreen = Screens::MAIN_MENU;

	LevelId currentLevel;
	
	int32_t currentStage = 0;
	
	int32_t gameTime;

	int32_t level = 1;

	float timeCounter = 0.0f;

	bool isPaused = false;

	bool resized = false;
};
