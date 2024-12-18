#include "LevelHandlingModule.hpp"
#include "SFML/Graphics.hpp"
#include "LevelData.hpp"
#include "Level.hpp"
#include <Common/Logs.hpp>

LevelId LevelHandlingModule::loadLevel(const std::string& baseLevelConfigPath)
{
	//create a new level and store it in the vector
	auto newLevel = std::make_shared<Level>(baseLevelConfigPath);

	//initialize level
	if (!newLevel->initialize())
	{
		LOG("Failed to initialize level from path : " + baseLevelConfigPath);
		return INVALID_LEVEL_ID;
	}

	//add level in map
	m_levelId++;
	m_levels[m_levelId] = newLevel;

	return m_levelId;
}

bool LevelHandlingModule::loadLevels(const std::vector<std::string>& configPaths)
{
	//temp level id vector
	std::vector<LevelId> loadedLevelIds;

	for (const auto& configPath : configPaths)
	{
		LevelId id = loadLevel(configPath);

		if (id == INVALID_LEVEL_ID)
		{
			LOG("Failed to load all levels. Partial levels will be discarded.");

			// Unload any successfully loaded levels
			for (LevelId loadedId : loadedLevelIds)
			{
				unloadLevel(loadedId);
			}

			loadedLevelIds.clear();
			return false;
		}

		loadedLevelIds.push_back(id);
	}
	return true;
}

bool LevelHandlingModule::setUpElementsOnLevel(int32_t levelElementsId)
{
	if (isLevelLoaded(m_currentLevel))
		return m_levels[m_currentLevel]->setUpElements(levelElementsId);

	return false;
}

bool LevelHandlingModule::unloadLevel(LevelId levelId)
{
	auto it = m_levels.find(levelId);

	if (it == m_levels.end())
	{
		LOG("Level does not exist with level id : " + std::to_string(levelId));
		return false;
	}

	// Reset the level and remove it from the map
	it->second.reset();
	m_levels.erase(it);

	return true;
}

void LevelHandlingModule::setCurrentLevel(LevelId levelId)
{
	//set loaded level as current 
	if (isLevelLoaded(levelId))
	{
		m_currentLevel = levelId;
	}
	else 
	{
		LOG("Attempted to set a non-loaded level as current.");
	}
}

LevelId LevelHandlingModule::getCurrentLevel()
{
	return m_currentLevel;
}

bool LevelHandlingModule::isLevelLoaded(LevelId levelId) const
{
	// Check if the level ID exists in the map
	return m_levels.find(levelId) != m_levels.end();
}

void LevelHandlingModule::setLevelViewOffset(const sf::Vector2f& offset, const sf::RenderWindow& window)
{
	//set level view based on player position
	if (isLevelLoaded(m_currentLevel))
		m_levels[m_currentLevel]->setViewOffset(offset, window);
}

TileInfo LevelHandlingModule::getTileInfo(int32_t x, int32_t y)
{
	if (isLevelLoaded(m_currentLevel))
	{
		auto info = m_levels[m_currentLevel]->getTileInfos(x, y);
		return info;
	}

	LOG("Can't return tile info, level is not loaded");
	return TileInfo();
}

std::vector<sf::Vector2f> LevelHandlingModule::getWalkablePositions() const
{
	auto it = m_levels.find(m_currentLevel);

	if (it != m_levels.end())
	{
		return it->second->getWalkablePositions();
	}

	LOG("Level not found");
	return std::vector<sf::Vector2f>();
}

std::vector<sf::Vector2f> LevelHandlingModule::getUnbreakableObstaclePositions() const
{
    auto it = m_levels.find(m_currentLevel);

    if (it != m_levels.end())
    {
        return it->second->getUnbreakableObstaclePositions();
    }

    LOG("Level not found");
    return std::vector<sf::Vector2f>();
}


void LevelHandlingModule::update(float, sf::Window* window)
{
	if (isLevelLoaded(m_currentLevel))
	{
		//draw level on screen
		auto* renderWindow = dynamic_cast<sf::RenderWindow*>(window);
		m_levels[m_currentLevel]->draw(*renderWindow, sf::RenderStates::Default);
	}
}

void LevelHandlingModule::terminate()
{
	// Reset all levels and clear the map
	for (auto& level : m_levels)
		level.second.reset();

	//clear level map
	m_levels.clear();
}
