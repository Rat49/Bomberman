#include "TestModule/LevelGeneratorTest.hpp"
#include "Common/Logs.hpp"

const std::string& LevelGeneratorTest::getName() const
{
	return Name;
}

void LevelGeneratorTest::setup()
{
	LOG("Setup done!");
}

void LevelGeneratorTest::run()
{
	//LevelGenerator* levelGenerator = LevelGenerator::generateLevel(11, 11, GameLevelType::Easy, 2, 5, { 1, 1 }, 2);

	//levelGenerator->exportLevelToTextFiles("LevelTest");

	// test
	//sf::Vector2i tilePosition = { 5, 5 };
	//if (levelGenerator->isObjectOnTile(tilePosition, levelGenerator->getObstacles()))
	//{
		LOG("Obstacle is on this tile!");
	//}

	//if (levelGenerator)
	//{
		//delete levelGenerator;
	//}
}

void LevelGeneratorTest::update(float deltaTime, sf::RenderWindow* window)
{
	(void)deltaTime;

	window->clear();
	window->display();

	completed = true;
}

bool LevelGeneratorTest::isComplete() const
{
	return completed;
}