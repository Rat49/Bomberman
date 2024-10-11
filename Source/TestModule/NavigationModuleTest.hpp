#pragma once
#include "TestModule/TestBase.hpp"
#include <iostream>

class NavigationModule;

class NavigationModuleTest : public TestBase
{
public:
	const std::string& getName() const override;
	void setup() override;
	void run() override;
	void update(float deltaTime) override { deltaTime = 0.0f; }
	bool isComplete() const override { return true; };

private:
	//mainly used for debugging
	void navigate(std::pair<int, int>& playerPosition, std::pair<int, int>& enemyPosition);

	//prints out a colored char from a grid
	void color(int i, int j);

	//moves an enemy in a random direction that isn't occupied by the player
	void moveEnemy(std::pair<int, int>& enemyPosition, bool updateEnemy);

	const std::string Name = "NavigationModuleTest";
	NavigationModule* nav;
};