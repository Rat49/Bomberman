#include "GameStats.hpp"
#include "Common/Modules.hpp"
#include "EventSystem/EventSystem.hpp"

void GameStats::initialize(std::shared_ptr<LevelController>& levelController, int32_t* time)
{
	m_enemieDeathID = Modules::Events->registerEvent();
	m_obstacleDestructionID = Modules::Events->registerEvent();
	m_boosterCollectID = Modules::Events->registerEvent();

	for (auto& enemie : levelController->getEnemies())
	{
		enemie.setCallbackID(m_enemieDeathID);
	}

	for (auto& obstacle : levelController->getObstacles())
	{
		obstacle.setCallbackID(m_obstacleDestructionID);
	}

	for (auto& booster : levelController->getBoosters())
	{
		booster.setCallbackID(m_boosterCollectID);
	}

	Modules::Events->subscribe(m_enemieDeathID, std::bind(&GameStats::onEnemieDeath, this));
	Modules::Events->subscribe(m_obstacleDestructionID, std::bind(&GameStats::onObstacleDestroyed, this));
	Modules::Events->subscribe(m_boosterCollectID, std::bind(&GameStats::onBoosterCollected, this));

	m_time = time;

	m_levelController = levelController;
}

void GameStats::onEnemieDeath()
{
	m_points += 10;
}

void GameStats::onBoosterCollected()
{
	m_points += 5;
}
void GameStats::onObstacleDestroyed()
{
	m_points += 3;
}

void GameStats::levelChange()
{
	for (auto& enemie : m_levelController->getEnemies())
	{
		enemie.setCallbackID(m_enemieDeathID);
	}

	for (auto& obstacle : m_levelController->getObstacles())
	{
		obstacle.setCallbackID(m_obstacleDestructionID);
	}

	for (auto& booster : m_levelController->getBoosters())
	{
		booster.setCallbackID(m_boosterCollectID);
	}

	if (*m_time > 0)
	{
		m_points += static_cast<int32_t>(*m_time);
	}
}

