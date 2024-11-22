#pragma once

#include "TestModule/TestBase.hpp"
#include "GameModule/LevelGenerator.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

class LevelGeneratorTest : public TestBase
{
public:
	const std::string& getName() const override;
	void setup() override;
	void run() override;
	void update(float deltaTime, sf::RenderWindow* window) override;
	bool isComplete() const override;

private:
	std::string Name = "LevelGeneratorTest";
	bool completed = false;
};
