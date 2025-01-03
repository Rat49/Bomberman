#include "LevelHandlingModuleTest.hpp"
#include "Common/Logs.hpp"
#include "Common/Modules.hpp"
#include "LevelHandlingModule/Level.hpp"
#include "LevelHandlingModule/LevelHandlingModule.hpp"
#include <chrono>
#include <thread>

namespace
{
const std::string TEST_LEVEL = "../../Data/Config/TestLevel1.ini";
}

const std::string& LevelHandlingModuleTest::getName() const
{
    return m_name;
}

void LevelHandlingModuleTest::setup()
{
    m_firstLevel = Modules::Level->loadLevel(TEST_LEVEL);
    Modules::Level->setCurrentLevel(m_firstLevel);
}

void LevelHandlingModuleTest::run()
{
    LOG("Run Level Handling Module Test");
    Modules::Level->getTileInfo(1, 1);
}

void LevelHandlingModuleTest::update(float, sf::RenderWindow* window)
{
    ////test level view based on player position
    sf::Vector2f playerPosition(600.f, 600.f);

    //set Level view using an offset
    Modules::Level->setLevelViewOffset(playerPosition, *window);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

bool LevelHandlingModuleTest::isComplete() const
{
    return true;
}
