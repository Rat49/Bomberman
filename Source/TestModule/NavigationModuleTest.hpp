#pragma once
#include "TestModule/TestBase.hpp"
#include "NavigationModule/Navigation.hpp"
#include <iostream>
#include <memory>

class NavigationModule;

class NavigationModuleTest : public TestBase
{
public:
	const std::string& getName() const override;
	void setup() override;
	void run() override;
	void update(float, sf::RenderWindow*) override {  }
	bool isComplete() const override { return true; };

private:
	//mainly used for debugging
	void navigate(sf::Vector2i& playerPosition, std::vector<sf::Vector2i>& enemyPositions);

	//prints out a colored char from a grid
	void color(int i, int j);

	//checks if tile is occupied and colors it if it is
	const bool checkOcuppied(const sf::Vector2i& playerPosition,
							const sf::Vector2i& enemyPosition,
							int i , int j);

	const std::string Name = "NavigationModuleTest";
	std::unique_ptr<NavigationModule> nav;
};