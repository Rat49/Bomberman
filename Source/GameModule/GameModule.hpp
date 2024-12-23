#pragma once
#include "BaseModule/BaseModule.hpp"
#include "UISystem/UIScreen.hpp"
#include "UIConstants.hpp"
#include "PlayerCharacter.hpp"
#include "LevelHandlingModule/LevelHandlingModule.hpp"
#include "Boosters/BoosterComponent.hpp"
#include <functional>

/*
* This is a general manger class. Holder of all modules. You can access it from any part of the game
*/

using EventID        = int32_t;
using FunctionHandle = int32_t;
using Callback       = std::function<void(void*)>;

class GameModule : public BaseModule
{
public:
    // Declare the game-specific event IDs here
    EventID GAME_TIMER_FINISHED;
    EventID QUEST_FAILED;
    EventID PLAYER_DESTROYED;
    EventID OBJECTIVE_COMPLETED;

	bool initialize() override;

	void run();

	void terminate() override;

	void setCurrentScreen(const Screens& newScreen);

	void setIsPaused(bool newPaused) { isPaused = newPaused; }

	bool getIsPaused() const { return isPaused; }

	// Method for handling resize event (changing resolution, mode)
	void handleResize(float x, float y);

	const std::string& getGameTitle() const { return gameTitle; }
	
	// Add new score into leader board
	void addScore(int32_t newScore, const std::string& name);

	float getHUDHeight();

	int32_t getCurrentStage() const { return currentStage; }

private:

	void addBooster(std::shared_ptr<BoosterComponent> newBooster);

	void removeAllBoosters();

	void updateBoosters();

	// Save leader board results into save file
	void saveResults();
	
	void checkTimeCounter();

	sf::RenderWindow window;

	PlayerCharacter player;
	
	LevelId currentLevel;
	
	std::unordered_map<Screens, std::shared_ptr<UIScreen>> screens;

	std::map<int32_t, std::shared_ptr<BoosterComponent>> m_boosters;

	Screens currentScreen = Screens::MAIN_MENU;
	
	int32_t currentStage = 0;
	
	int32_t gameTime;

	int32_t elementsId = 1;

	float timeCounter = 0.0f;

	bool isPaused = false;

	// RenderWindow doesn't have method getTitle
	// We need this for creating new windows (changing resolution)
	std::string gameTitle;
	
	bool resized = false;

};
