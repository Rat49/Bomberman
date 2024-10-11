#pragma once

#include <vector>
#include <utility>

class Algorithm;

class NavigationModule {

public:
	NavigationModule() = default;
	NavigationModule(std::vector<std::vector<char>>& grid/*, some parameter for mapping the grid*/);

	//Algorithm used for navigation
	Algorithm* algorithm;

	//mapped grid of players environment for now char of tiles
	std::vector<std::vector<char>> grid;
private:

	//called to parse our game into a grid
	void parseGrid(/*some representation of our game environment*/);

};