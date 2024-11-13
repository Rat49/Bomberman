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

bool LevelHandlingModule::isLevelLoaded(LevelId levelId) const
{
	return levelId < m_levels.size() && m_levels[levelId] != nullptr;
}

void LevelHandlingModule::setLevelViewOffset(const sf::Vector2f& offset, const sf::RenderWindow& window)
{
	//set level view based on player position
	if (isLevelLoaded(m_currentLevel))
	{
		m_levels[m_currentLevel]->setViewOffset(offset, window);
	}
}

void LevelHandlingModule::update(float, sf::Window* window)
{
	//draw level on window
	if (isLevelLoaded(m_currentLevel))
	{
		auto* renderWindow = dynamic_cast<sf::RenderWindow*>(window);
		m_levels[m_currentLevel]->draw(*renderWindow, sf::RenderStates::Default);
	}
}

void LevelHandlingModule::terminate()
{
	for (auto& level : m_levels)
	{
		level.reset();
	}

	m_levels.clear();
}
