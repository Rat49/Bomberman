#include "LevelHandlingModule.hpp"
#include "SFML/Graphics.hpp"
#include "LevelData.hpp"
#include "Level.hpp"
#include <Common/Logs.hpp>

LevelId LevelHandlingModule::loadLevel(const std::string& configPath)
{
	//create a new level and store it in the vector
	auto newLevel = std::make_shared<Level>(configPath);
	m_levels.push_back(newLevel);

	//return the index of created level
	return static_cast<int32_t>(m_levels.size() - 1);
}

std::vector<LevelId> LevelHandlingModule::loadLevels(const std::vector<std::string>& configPaths)
{
	//temporary vector to store level ids
	std::vector<LevelId> tmpLevelIds;

	//go through config vector and load levels
	for (const auto& configPath : configPaths)
	{
		LevelId id = loadLevel(configPath);
		tmpLevelIds.push_back(id);
	}

	//return all ids of loaded levels
	return tmpLevelIds;
}

std::shared_ptr<Level> LevelHandlingModule::getLevel(LevelId levelId) const
{
	//return level based on id 
	if (levelId < m_levels.size())
		return m_levels[levelId];

	return nullptr;
}

void LevelHandlingModule::drawLevel(sf::RenderWindow& window, LevelId levelId) const
{
	//draw level on window
	if (isLevelLoaded(levelId))
	{
		m_levels[levelId]->draw(window, sf::RenderStates::Default);
	}
}

bool LevelHandlingModule::isLevelLoaded(LevelId levelId) const
{
	return levelId < m_levels.size() && m_levels[levelId] != nullptr;
}

void LevelHandlingModule::destroyTileFromLevel(LevelId levelId, int32_t x, int32_t y)
{
	//destroy tile using coordinates
	if (isLevelLoaded(levelId))
	{
		m_levels[levelId]->destroyTile(x, y);
	}
}

bool LevelHandlingModule::isWalkable(LevelId levelId, const int32_t x, const int32_t y)
{
	//return if it's ground
	if (isLevelLoaded(levelId))
	{
		return m_levels[levelId]->isTileWalkable(x, y);
	}
	
	return false;
}

TileType LevelHandlingModule::getTileType(LevelId levelId, int32_t x, int32_t y)
{
	if (isLevelLoaded(levelId))
	{
		return m_levels[levelId]->getTileType(x, y);
	}

	return TileType::Unknown;
}

void LevelHandlingModule::terminate()
{
	for (auto& level : m_levels)
	{
		level.reset();
	}

	m_levels.clear();
}
