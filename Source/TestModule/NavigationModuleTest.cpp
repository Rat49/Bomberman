#include "NavigationModuleTest.hpp"
#include "NavigationModule/Algorithm.hpp"
#include <functional>
#include <thread>
#include <chrono>
#include <iostream>
#include <random>
#include <memory>

namespace{
	constexpr const char* RESET = "\033[0m";
	constexpr const char* RED = "\033[31m";
	constexpr const char* GREEN = "\033[32m";
	constexpr const char* YELLOW = "\033[33m";
	constexpr const char* BLUE = "\033[34m";
	constexpr const char* MAGENTA = "\033[35m";
	constexpr const char* CYAN = "\033[36m";
	constexpr const char* WHITE = "\033[37m";
}

const std::string& NavigationModuleTest::getName() const
{
	return Name;
}

void NavigationModuleTest::setup(){
	std::vector<std::vector<bool>> grid = { //standard grid for bomberman
			{1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,1,0,1,0,1,0,1},
			{1,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,1,0,1,0,1,0,1},
			{1,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,1,0,1,0,1,0,1},
			{1,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1}
	};

	nav = std::make_unique<NavigationModule>(grid);
}

void NavigationModuleTest::run(){
	sf::Vector2i playerPosition{ 1, 1 };
	std::vector<sf::Vector2i> enemyPositions = { { 4, 9 },{ 7, 9 } };

	navigate(playerPosition, enemyPositions);
}

//prints out the path finding process as well as execution time of every iteration
//mainly used for debugging
void NavigationModuleTest::navigate(sf::Vector2i& playerPosition, std::vector<sf::Vector2i>& enemyPositions) {

	sf::Vector2i moveTo;

	while (playerPosition != enemyPositions[1]) {
		std::cout << CYAN << "LEGEND" << RESET << std::endl;
		std::cout << GREEN << "P = Player" << RESET << std::endl;
		std::cout << GREEN << "V = Visited" << RESET << std::endl;
		std::cout << RED << "E = Enemy" << RESET << std::endl;
		std::cout << MAGENTA << "G = Grass" << RESET << std::endl;
		std::cout << YELLOW << "O = Obstacle" << RESET << std::endl;
		for (int i = 0; i < nav->grid.size(); i++) {
			for (int j = 0; j < nav->grid[0].size(); j++) {
				if(!checkOcuppied(playerPosition, enemyPositions[0], i, j) &&
					!checkOcuppied(playerPosition, enemyPositions[1], i, j))
					color(i, j);
			}
			std::cout << std::endl;
		}
		//record the time it takes for function to exec
		auto start = std::chrono::high_resolution_clock::now();

		nav->algorithm->navigate(playerPosition);

		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

		//change the enemy location
		nav->algorithm->moveTo(enemyPositions[0], moveTo);
		enemyPositions[0] = moveTo;
		nav->algorithm->moveTo(enemyPositions[1], moveTo);
		enemyPositions[1] = moveTo;

		//sleep so we can see the output and clear it after
		std::this_thread::sleep_for(std::chrono::seconds(2));
		system("cls");
	}
}

//prints out a colored char from a grid
void NavigationModuleTest::color(int i, int j) {
	std::string fill;
	bool c = nav->grid[i][j];
	char out = 'O';
	switch (c) {
	case 0: { fill = MAGENTA; out = 'G';  break; }
	default: { fill = YELLOW; out = 'O'; break; }
	}
	std::cout << fill << out << RESET;
}

const bool NavigationModuleTest::checkOcuppied(const sf::Vector2i& playerPosition,
	const sf::Vector2i& enemyPosition,
	int i, int j) {

	if (playerPosition.x == i && playerPosition.y == j) {
		std::cout << GREEN << "P" << RESET;
		return true;
	}
	if (enemyPosition.x == i && enemyPosition.y == j) {
		std::cout << RED << "E" << RESET;
		return true;
	}
	return false;
}
