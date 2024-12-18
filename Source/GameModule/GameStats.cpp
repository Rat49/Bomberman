#include "GameStats.hpp"
#include "Common/Modules.hpp"
#include "EventSystem/EventSystem.hpp"
#include "ConfigSystem/ConfigSystem.hpp"

#include "Common/Logs.hpp"

namespace 
{
	const std::string PATH_WALKING_ANIMATION = "../../Data/Config/PointsConfig.ini";
	const std::string AMOUNT = "amount";
	const std::string ENEMY = "EnemyKill";
	const std::string BOOSTER = "BoosterFound";
	const std::string OBSTACLE = "ObstacleDestroy";
}

void GameStats::initialize(std::shared_ptr<LevelController>& levelController, int32_t* time)
{
	Modules::Config->addFile(PATH_WALKING_ANIMATION);
	const ConfigFile& walkingAnimations = Modules::Config->getFile(PATH_WALKING_ANIMATION);
	
	m_enemieKillPoints = walkingAnimations.getSection(ENEMY).getValue(AMOUNT).getInt32();
	m_boosterCollectPoints = walkingAnimations.getSection(BOOSTER).getValue(AMOUNT).getInt32();
	m_obstacleDestructionPoints = walkingAnimations.getSection(OBSTACLE).getValue(AMOUNT).getInt32();

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

	m_enemieDeathHandle = Modules::Events->subscribe(m_enemieDeathID, std::bind(&GameStats::onEnemieDeath, this));
	m_obstacleDestructionHandle = Modules::Events->subscribe(m_obstacleDestructionID, std::bind(&GameStats::onObstacleDestroyed, this));
	m_boosterCollectHandle = Modules::Events->subscribe(m_boosterCollectID, std::bind(&GameStats::onBoosterCollected, this));

	m_time = time;

	m_levelController = levelController;
}

GameStats::~GameStats()
{
	Modules::Events->unsubscribe(m_enemieDeathID, m_enemieDeathHandle);
	Modules::Events->unsubscribe(m_obstacleDestructionID, m_obstacleDestructionHandle);
	Modules::Events->unsubscribe(m_boosterCollectID, m_boosterCollectHandle);
}

void GameStats::onEnemieDeath()
{
	m_points += m_enemieKillPoints;
}

void GameStats::onBoosterCollected()
{
	m_points += m_boosterCollectPoints;
}
void GameStats::onObstacleDestroyed()
{
	m_points += m_obstacleDestructionPoints;
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

