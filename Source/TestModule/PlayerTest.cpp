#include "TestModule/PlayerTest.hpp"
#include "Common/Logs.hpp"
#include "Common/Modules.hpp"
#include "SpriteModule/Animation.hpp"

const std::string& PlayerTest::getName() const
{
    return Name;
}

void PlayerTest::setup()
{
    LOG("PlayerTest: setup()");
}

void PlayerTest::run()
{
    LOG("PlayerTest: run()");
}

void PlayerTest::update(float, sf::RenderWindow* window)
{
    window->draw(*player.getCurrentAnimation());
    player.setIsUpdated(false);
}

bool PlayerTest::isComplete() const
{
    return false;
}
