#include "LevelHandlingModule.hpp"
#include "LevelData.hpp"
#include "Level.hpp"


void LevelHandlingModule::createLevel(const std::string& configPath)
{
	m_level = std::make_unique<Level>(configPath);
}

void LevelHandlingModule::draw(sf::RenderWindow& window) const
{
	if (m_level) 
	{
		window.draw(*m_level);
	}
}

bool LevelHandlingModule::isLevelLoaded() const
{
	return m_level != nullptr;
}

void LevelHandlingModule::terminate()
{}
