#include "LevelHandlingModuleTest.hpp"
#include "LevelHandlingModule/LevelHandlingModule.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"
#include <chrono>
#include <thread>

namespace 
{
	const std::string LEVEL1_CONFIG_PATH = "../../Data/Config/Level_1_ConfigTest.ini";
	const std::string LEVEL2_CONFIG_PATH = "../../Data/Config/Level_2_ConfigTest.ini";
}

const std::string& LevelHandlingModuleTest::getName() const
{
	return m_name;
}

void LevelHandlingModuleTest::setup()
{
	//load individual levels one by one
	m_firstLevel = Modules::Level->loadLevel(LEVEL1_CONFIG_PATH);
	m_secondLevel = Modules::Level->loadLevel(LEVEL2_CONFIG_PATH);

	/*
	*load multiple levels at once using vector of config paths
	
	std::vector<std::string> configPaths = { LEVEL1_CONFIG_PATH, LEVEL2_CONFIG_PATH };
	auto levelIds = Modules::Level->loadLevels(configPaths);

	/*/

}

void LevelHandlingModuleTest::run()
{
	LOG("Run LevelHandlingModuleTest");

	//Test if tile is walkable (ground)
	if (Modules::Level->isWalkable(m_firstLevel, 1, 4))
		LOG("Walkable");


	/*Test the tile type value based on coordinates */
	if (TileType::Ground == Modules::Level->getTileType(m_firstLevel, 4, 2))
	{
		LOG(" TILE TYPE IS : GROUND");
	}
	else if (TileType::Wall == Modules::Level->getTileType(m_firstLevel, 4, 2))
	{
		LOG(" TILE TYPE IS : WALL");
	}
	else
	{
		LOG(" TILE TYPE IS : DESTROYABLE WALL");
	}
}

void LevelHandlingModuleTest::update(float, sf::RenderWindow* window)
{
	if (!Modules::Level->isLevelLoaded(m_firstLevel))
		return;

	window->setSize(sf::Vector2u(800, 600));
	window->clear();

	//draw loaded level based on id 
	Modules::Level->drawLevel(*window, m_firstLevel);

	window->display();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

bool LevelHandlingModuleTest::isComplete() const
{
	return false;
}
