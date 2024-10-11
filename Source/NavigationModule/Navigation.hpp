#pragma once

#include <vector>
#include <utility>

class Algorithm;

class NavigationModule {

public:
	NavigationModule(/*, some parameter for mapping the grid*/);

	//Algorithm used for navigation
	Algorithm* algorithm;

private:

	//mapped grid of players environment
	std::vector<std::vector<char>> grid;

	//called to parse our game into a grid
	void parseGrid(/*some representation of our game environment*/);

};