#pragma once

#include <vector>
#include <utility>

class Algorithm;

class NavigationModule {

public:
	NavigationModule() = default;
	NavigationModule(std::vector<std::vector<bool>>& grid/*, some parameter for mapping the grid*/);

	//Algorithm used for navigation
	Algorithm* algorithm;

	//mapped grid of players environment for now char of tiles
	std::vector<std::vector<bool>> grid;
private:

	//called to parse our game into a grid
	void parseGrid(/*some representation of our game environment*/);

};