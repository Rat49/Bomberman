#include "Navigation.hpp" 
#include "Algorithm.hpp"

NavigationModule::NavigationModule(std::vector<std::vector<bool>>& grid/*, some parameter for mapping the grid*/) : grid(grid) {

	// grid will be initialized by the second parameter
	// grid = parseGrid(/*some parameter for mapping the grid*/);

	//construct an algorithm for navigation based on config input
	algorithm = new AStar(this->grid); 
}

//called to parse our game into a grid
void NavigationModule::parseGrid(/*some representation of our game environment*/) {

}