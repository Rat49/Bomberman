#pragma once
#include "BaseModule/BaseModule.hpp"
#include "UISystem/UIScreen.hpp"
#include "GameModule/LevelGenerator.hpp"
#include "UIConstants.hpp"
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

	void setIsPaused(bool newPaused) { isPaused = newPaused; }

	bool getIsPaused() const { return isPaused; }

	// Method for handling resize event (changing resolution, mode)
	void handleResize(float x, float y);

	const std::string& getGameTitle() const { return gameTitle; }

private:
	void addBooster(std::shared_ptr<BoosterComponent> newBooster);

	void removeAllBoosters();

	void updateBoosters();

	sf::RenderWindow window;

	std::unordered_map<Screens, std::shared_ptr<UIScreen>> screens;

	std::map<int32_t, std::shared_ptr<BoosterComponent>> m_boosters;

	Screens currentScreen = Screens::MAIN_MENU;

	float timeCounter = 0.0f;
	int32_t currentStage = 0;

	int32_t gameTime;

	bool isPaused = false;

	void checkTimeCounter();

	PlayerCharacter player;

	std::unique_ptr<LevelGenerator> levelGenerator;
	 
	LevelId currentLevel;

	// RenderWindow doesn't have method getTitle
	// We need this for creating new windows (changing resolution)
	std::string gameTitle;
};
