#include "TestModule/LevelGeneratorTest.hpp"

const std::string& LevelGeneratorTest::getName() const
{
	return Name;
}

void LevelGeneratorTest::setup()
{

}

void LevelGeneratorTest::run()
{
	LevelGenerator levelGenerator;
	levelGenerator.Initialize(11, 11, GameLevelType::Easy, 2, 5, { 1, 1 });
	levelGenerator.generateLevel(11, 11, GameLevelType::Easy, 2, 5, { 1, 1 }, 2);
	levelGenerator.exportLevelToTextFiles("LevelTest");
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