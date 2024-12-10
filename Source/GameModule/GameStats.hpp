#pragma once
#include "LevelController.hpp"
#include <memory>

class GameStats
{
public:
	GameStats(const std::vector<Enemy>& enemies, const std::vector<Booster>& boosters, const std::vector<Obstacle>& obstacles, int32_t* time);
	void updateLevelStats();
	int32_t getPoints() const { return m_points; }
	void resetPoints() { m_points = 0; } // reset when player looses all of the lives
	void levelChange(); // updates sizes of vectors and applies remaining time  score += m_time
private:
	const std::vector<Enemy>& m_enemies;
	const std::vector<Booster>& m_boosters;
	const std::vector<Obstacle>& m_obstacles;

	int32_t m_enemiesSize;
	int32_t m_boostersSize;
	int32_t m_obstaclesSize;
	int32_t* m_time;

	int32_t m_points = 0;
};

