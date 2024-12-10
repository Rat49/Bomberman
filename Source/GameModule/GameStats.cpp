#include "GameStats.hpp"
#include "Common/Logs.hpp"

GameStats::GameStats(const std::vector<Enemy>& enemies, const std::vector<Booster>& boosters, const std::vector<Obstacle>& obstacles, int32_t* time)
	: m_enemies(enemies), m_boosters(boosters), m_obstacles(obstacles), m_time(time)
{
	m_enemiesSize = static_cast<int32_t>(m_enemies.size());
	m_boostersSize = static_cast<int32_t>(m_boosters.size());
	m_obstaclesSize = static_cast<int32_t>(m_obstacles.size());
}

void GameStats::updateLevelStats()
{
	if (m_enemiesSize > m_enemies.size())
	{
		m_points += ((m_enemiesSize - static_cast<int32_t>(m_enemies.size())) * 10);
		m_enemiesSize = static_cast<int32_t>(m_enemies.size());
	}

	if (m_boostersSize > m_boosters.size())
	{
		m_points += ((m_boostersSize - static_cast<int32_t>(m_boosters.size())) * 5);
		m_boostersSize = static_cast<int32_t>(m_boosters.size());
	}

	if (m_obstaclesSize > m_obstacles.size())
	{
			m_points += ((m_obstaclesSize - static_cast<int32_t>(m_obstacles.size())) * 3);
			m_obstaclesSize = static_cast<int32_t>(m_obstacles.size());
	}
}

void GameStats::levelChange()
{
	m_enemiesSize = static_cast<int32_t>(m_enemies.size());
	m_boostersSize = static_cast<int32_t>(m_boosters.size());
	m_obstaclesSize = static_cast<int32_t>(m_obstacles.size());
	if (*m_time > 0) 
	{
		m_points += static_cast<int32_t>(*m_time);
	}
}

