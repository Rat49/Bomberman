#pragma once

//THIS FILE HOLD ALL THE DEBUG CODE IT WILL BE MOVED TO TESTING MODULES 
//THIS FILE IS TEMPORARY

/*

h

namespace Color {
	constexpr const char* RESET = "\033[0m";
	constexpr const char* RED = "\033[31m";
	constexpr const char* GREEN = "\033[32m";
	constexpr const char* YELLOW = "\033[33m";
	constexpr const char* BLUE = "\033[34m";
	constexpr const char* MAGENTA = "\033[35m";
	constexpr const char* CYAN = "\033[36m";
	constexpr const char* WHITE = "\033[37m";
}

using namespace Color;

//prints out the path finding process as well as execution time of every iteration
//as well as matrix of all evaluated nodes for each iteration
//mainly used for debugging
void print(std::pair<int, int>& playerPosition, std::pair<int, int>& enemyPosition);

//mapped grid of explored environment
std::vector<std::vector<char>> gridBfs;

//prints out a colored char from a grid
	void color(int i, int j, bool w);

//moves an enemy in a random direction that isn't occupied by the player
void moveEnemy(std::pair<int, int>& enemyPosition, bool updateEnemy);

cpp

grid = { //standard grid for bomberman
			{'O','O','O','O','O','O','O','O','O','O','O'},
			{'O','P','G','G','G','G','G','G','G','G','O'},
			{'O','G','O','G','O','G','O','G','O','G','O'},
			{'O','G','G','G','G','G','G','G','G','G','O'},
			{'O','G','O','G','O','G','O','G','O','E','O'},
			{'O','G','G','G','G','G','G','G','G','G','O'},
			{'O','G','O','G','O','G','O','G','O','G','O'},
			{'O','G','G','G','G','G','G','G','G','G','O'},
			{'O','O','O','O','O','O','O','O','O','O','O'}
	};
	gridBfs = grid;


//prints out the path finding process as well as execution time of every iteration
//as well as matrix of all evaluated nodes for each iteration
//mainly used for debugging
void NavigationModule::print(std::pair<int, int>& playerPosition, std::pair<int, int>& enemyPosition) {

	std::pair<int, int> moveTo;
	bool updateEnemy = true;

	while (playerPosition != enemyPosition) {
		std::cout << CYAN << "LEGEND" << RESET << std::endl;
		std::cout << GREEN << "P = Player" << RESET << std::endl;
		std::cout << GREEN << "V = Visited" << RESET << std::endl;
		std::cout << RED << "E = Enemy" << RESET << std::endl;
		std::cout << MAGENTA << "G = Grass" << RESET << std::endl;
		std::cout << YELLOW << "O = Obstacle" << RESET << std::endl;
		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid[0].size(); j++) {
				color(i, j, true);
			}
			std::cout << std::endl;
		}
		//record the time it takes for function to exec
		auto start = std::chrono::high_resolution_clock::now();

		algorithm->navigate(playerPosition, moveTo);

		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

		//print evaluation matrix
		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid[0].size(); j++) {
				color(i, j, false);
			}
			std::cout << std::endl;
		}
		//Change player location
		grid[playerPosition.first][playerPosition.second] = 'G';
		playerPosition.first += moveTo.first;
		playerPosition.second += moveTo.second;
		if (grid[playerPosition.first][playerPosition.second] == 'E')
			updateEnemy = false;
		grid[playerPosition.first][playerPosition.second] = 'P';
		//change the enemy location
		moveEnemy(enemyPosition, updateEnemy);
		gridBfs = grid;

		//sleep so we can see the output and clear it after
		std::this_thread::sleep_for(std::chrono::seconds(3));
		system("cls");
	}
}

//prints out a colored char from a grid
void NavigationModule::color(int i, int j, bool w) {
	std::string fill;
	char c = w == true ? grid[i][j] : gridBfs[i][j];
	switch (c) {
	case 'P':
	case 'V': fill = GREEN; break;
	case 'E': fill = RED; break;
	case 'O': fill = YELLOW; break;
	case 'G': fill = MAGENTA; break;
	default:
		break;
	}
	std::cout << fill << c << RESET;
}

//moves an enemy in a random direction that isn't occupied by the player
void NavigationModule::moveEnemy(std::pair<int, int>& enemyPosition, bool updateEnemy) {
	if (!updateEnemy)
		return;
	std::vector<std::pair<int, int>> actions;

	algorithm->returnActions(enemyPosition, actions);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, actions.size());

	int index = dist(gen);

	if (index < actions.size()) {
		auto action = actions[index];
		grid[enemyPosition.first][enemyPosition.second] = 'G';
		enemyPosition = action;
		grid[enemyPosition.first][enemyPosition.second] = 'E';
	}
}

includes 

#include <functional>
#include <thread>
#include <chrono>
#include <iostream>

*/