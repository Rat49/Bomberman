#include "NavigationModuleTest.hpp"
#include "NavigationModule/Navigation.hpp"
#include "NavigationModule/Algorithm.hpp"
#include "NavigationModule/NavigationEnum.hpp"
#include <functional>
#include <thread>
#include <chrono>
#include <iostream>
#include <random>

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

	nav = new NavigationModule(grid);
}

void NavigationModuleTest::run(){
	std::pair<int, int> playerPosition{ 1, 1 };
	std::pair<int, int> enemyPosition{ 4, 9 };

	navigate(playerPosition, enemyPosition);
}

//prints out the path finding process as well as execution time of every iteration
//mainly used for debugging
void NavigationModuleTest::navigate(std::pair<int, int>& playerPosition, std::pair<int, int>& enemyPosition) {

	std::pair<int, int> moveTo;
	bool updateEnemy = true;

	while (playerPosition != enemyPosition) {
		std::cout << CYAN << "LEGEND" << RESET << std::endl;
		std::cout << GREEN << "P = Player" << RESET << std::endl;
		std::cout << GREEN << "V = Visited" << RESET << std::endl;
		std::cout << RED << "E = Enemy" << RESET << std::endl;
		std::cout << MAGENTA << "G = Grass" << RESET << std::endl;
		std::cout << YELLOW << "O = Obstacle" << RESET << std::endl;
		for (int i = 0; i < nav->grid.size(); i++) {
			for (int j = 0; j < nav->grid[0].size(); j++) {
				if(!checkOcuppied(playerPosition, enemyPosition, i, j))
					color(i, j);
			}
			std::cout << std::endl;
		}
		//record the time it takes for function to exec
		auto start = std::chrono::high_resolution_clock::now();

		nav->algorithm->navigate(playerPosition, enemyPosition, moveTo);

		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

		//Change player location
		playerPosition.first += moveTo.first;
		playerPosition.second += moveTo.second;
		if (playerPosition == enemyPosition)
			updateEnemy = false;
		//change the enemy location
		moveEnemy(enemyPosition, playerPosition, updateEnemy);

		//sleep so we can see the output and clear it after
		std::this_thread::sleep_for(std::chrono::seconds(2));
		system("cls");
	}
}

//prints out a colored char from a grid
void NavigationModuleTest::color(int i, int j) {
	std::string fill;
	int c = nav->grid[i][j];
	char out = 'O';
	switch (c) {
	case Passable: { fill = MAGENTA; out = 'G';  break; }
	case NotPassable: { fill = YELLOW; out = 'O'; break; }
	default:
		break;
	}
	std::cout << fill << out << RESET;
}

const bool NavigationModuleTest::checkOcuppied(const std::pair<int, int>& playerPosition,
	const std::pair<int, int>& enemyPosition,
	int i, int j) {
	if (playerPosition.first == i && playerPosition.second == j) {
		std::cout << GREEN << "P" << RESET;
		return true;
	}
	if (enemyPosition.first == i && enemyPosition.second == j) {
		std::cout << RED << "E" << RESET;
		return true;
	}
	return false;
}
//moves an enemy in a random direction that isn't occupied by the player
void NavigationModuleTest::moveEnemy(std::pair<int, int>& enemyPosition,const std::pair<int, int>& playerPosition, bool updateEnemy) {
	if (!updateEnemy)
		return;
	std::vector<std::pair<int, int>> actions;

	nav->algorithm->returnActions(enemyPosition,playerPosition, actions);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, static_cast<int>(actions.size()));

	int index = dist(gen);

	if (index < actions.size()) {
		auto action = actions[index];
		enemyPosition = action;
	}
}
