#pragma once
#include "LevelController.hpp"
#include <memory>
#include "EventSystem/EventTypes.hpp"

class GameStats
{
public:
	GameStats() = default;

	void initialize(std::shared_ptr<LevelController>& levelController, int32_t* time);

	void onEnemieDeath();

	void onBoosterCollected();

	void onObstacleDestroyed();

	int32_t getPoints() const { return m_points; }

	void resetPoints() { m_points = 0; } // reset when player looses all of the lives

	void levelChange(); // updates callbacks and applies remaining time  score += m_time
private:
	int32_t* m_time;

	int32_t m_points = 0;

	EventID m_enemieDeathID = -1;

	EventID m_obstacleDestructionID = -1;

	EventID m_boosterCollectID = -1;

	std::shared_ptr<LevelController> m_levelController;
};

