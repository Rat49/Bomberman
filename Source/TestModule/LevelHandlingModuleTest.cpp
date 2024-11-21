#include "LevelHandlingModuleTest.hpp"
#include "LevelHandlingModule/LevelHandlingModule.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"
#include "LevelHandlingModule/Level.hpp"
#include <chrono>
#include <thread>
#include "AssetManager/AssetManager.hpp"

namespace 
{
	const std::string BASE_LEVEL  = "../../Data/Config/BaseLevelConfig.ini";
}

const std::string& LevelHandlingModuleTest::getName() const
{
	return m_name;
}

void LevelHandlingModuleTest::setup()
{
	m_firstLevel = Modules::Level->loadLevel(BASE_LEVEL);
	Modules::Level->setCurrentLevel(m_firstLevel);
	//Modules::Level->setCurrentLevel(1);
	//Modules::Level->getLevel()->canWalkAndBreakTile(4, 1);
	//Modules::Level->getLevel()->getTilePosition(1, 1);
	//Modules::Level->getLevel()->setNewTile(1, 2, 2);
	//Modules::Level->getLevel()->getTilePosition(3, 3);
	//Modules::Level->getLevel()->getTileID(2, 2);
	//LOG("TILE ID: $", Modules::Level->getLevel()->getTileID(4, 1));
	//LOG("TILE STATE: $ ", Modules::Level->getLevel()->getTileState(0, 0));
	//LOG("TILE STATE: $ ", Modules::Level->getLevel()->getTileState(1, 1));
	//LOG("TILE STATE: $ ", Modules::Level->getLevel()->getTileState(1, 2));
	//LOG("row: $ | col: $", Modules::Level->getLevel()->getTileRowCol(100.f, 100.f).x, Modules::Level->getLevel()->getTileRowCol(100.f, 100.f).y );
}

void LevelHandlingModuleTest::run()
{
	LOG("Run Level Handling Module Test");
	Modules::Level->getTileInfo(1, 1);
}

void LevelHandlingModuleTest::update(float, sf::RenderWindow* window)
{
	////test level view based on player position
	sf::Vector2f playerPosition(1900.f, 1500.f); 

	//set Level view using an offset
	Modules::Level->setLevelViewOffset(playerPosition, *window);

	//std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

bool LevelHandlingModuleTest::isComplete() const
{
	return false;
}
