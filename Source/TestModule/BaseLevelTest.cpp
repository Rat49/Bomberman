#include "BaseLevelTest.hpp"
#include "LevelHandlingModule/LevelHandlingModule.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"
#include "LevelHandlingModule/Level.hpp"
#include "SpriteModule/SpriteModule.hpp"

namespace
{
	const std::string BASE_LEVEL = "../../Data/Config/BaseLevelConfig.ini";
}

const std::string& BaseLevelTest::getName() const
{
	return Name;
}

void BaseLevelTest::setup()
{
	LOG("BaseLevelTest: setup()");
	baseLevel = Modules::Level->loadLevel(BASE_LEVEL);
	Modules::Level->setCurrentLevel(baseLevel);
}

void BaseLevelTest::run()
{
	LOG("BaseLevelTest: run()");
}

void BaseLevelTest::update(float, sf::RenderWindow* window)
{
	Modules::Level->setLevelViewOffset(player.getCurrentPosition(), *window);
	window->draw(*player.getCurrentAnimation());
	player.setIsUpdated(false);
}

bool BaseLevelTest::isComplete() const
{
	return false;
}