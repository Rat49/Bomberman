#include "LevelHandlingModuleTest.hpp"
#include "LevelHandlingModule/LevelHandlingModule.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"
#include <chrono>
#include <thread>

namespace 
{
	const std::string LEVEL_CONFIG_PATH = "../../Data/Config/LevelConfigTest.ini";
}

const std::string& LevelHandlingModuleTest::getName() const
{
	return m_name;
}

void LevelHandlingModuleTest::setup()
{
	Modules::Level->createLevel(LEVEL_CONFIG_PATH);
}

void LevelHandlingModuleTest::run()
{
	LOG("Run LevelHandlingModuleTest");
}

void LevelHandlingModuleTest::update(float, sf::RenderWindow* window)
{
	if (!Modules::Level->isLevelLoaded())
		return;

	window->setSize(sf::Vector2u(800, 600));
	window->clear();

	Modules::Level->draw(*window);

	window->display();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

bool LevelHandlingModuleTest::isComplete() const
{
	return false;
}
