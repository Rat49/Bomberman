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
	//load levels
	m_firstLevel = Modules::Level->loadLevel(LEVEL1_CONFIG_PATH);
	m_secondLevel = Modules::Level->loadLevel(LEVEL2_CONFIG_PATH);


	//chose current game level
	Modules::Level->setCurrentLevel(m_firstLevel);
}

void LevelHandlingModuleTest::run()
{
	LOG("Run Level Handling Module Test");
}

void LevelHandlingModuleTest::update(float deltaTime, sf::RenderWindow* window)
{
	window->clear();

	//test level view based on player position
	sf::Vector2f playerPosition(300.f, 300.f);  

	//set Level view
	Modules::Level->setLevelViewOffset(playerPosition, *window);

	//draw level
	Modules::Level->update(deltaTime, window);

	window->display();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

bool LevelHandlingModuleTest::isComplete() const
{
	return false;
}
