#include "TestModule/PlayerTest.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"
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
	// on every move of player, IsUpdated variable in PlayerCharacter is set to true
	// on every update inside test that variable is checked, to check if animation needs to be redrawn 
	// after animation it is displayed, IsUpdated is set to false

	if (player.getIsUpdated()) {
		window->clear();
		window->draw(*player.getCurrentAnimation());
		window->display();
		player.setIsUpdated(false);
	}
}

bool PlayerTest::isComplete() const
{
	return false;
}
