#pragma once


#include "Algorithm.hpp"
#include "BaseModule/BaseModule.hpp"
#include <vector>
#include <utility>
#include <memory>

class AStar;

class NavigationModule : public BaseModule {

public:
	NavigationModule() = default;
	NavigationModule(std::vector<std::vector<bool>>& grid/*, some parameter for mapping the grid*/);

	//Algorithm used for navigation
	std::unique_ptr<AStar> algorithm;

	//mapped grid of players environment for now char of tiles
	std::vector<std::vector<bool>> grid;

	void terminate() override;
private:

	//called to parse our game into a grid
	void parseGrid(/*some representation of our game environment*/);

};