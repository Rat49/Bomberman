#pragma once

#include <vector>
#include <utility>
#include <functional> 
#include <thread>  
#include <chrono>
#include <stdio.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "Algorithm.hpp"

#define RESET   "\033[0m"  
#define RED     "\033[31m" 
#define GREEN   "\033[32m" 
#define YELLOW  "\033[33m" 
#define BLUE    "\033[34m" 
#define MAGENTA "\033[35m" 
#define CYAN    "\033[36m" 
#define WHITE   "\033[37m" 

class NavigationModule {

public:
	NavigationModule(int alg /*, some parameter for mapping the grid*/);

	//prints out the path finding process as well as execution time of every iteration
	//as well as matrix of all evaluated nodes for each iteration
	//mainly used for debugging
	void print(std::pair<int, int>& playerPosition, std::pair<int, int>& enemyPosition);

	//Algorithm used for navigation
	Algorithm* algorithm;

private:

	//mapped grid of players environment
	std::vector<std::vector<char>> grid;

	//mapped grid of explored environment
	std::vector<std::vector<char>> gridBfs;

	//called to parse our game into a grid
	void parseGrid(/*some representation of our game environment*/);

	//prints out a colored char from a grid 
	void color(int i, int j, bool w);

	//moves an enemy in a random direction that isn't occupied by the player
	void moveEnemy(std::pair<int, int>& enemyPosition, bool updateEnemy);

};