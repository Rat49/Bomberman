#pragma once

#include <vector>
#include <utility>
#include <functional> 
#include <unordered_set>
#include <unordered_map>
#include <queue>

class Algorithm {
public:
	Algorithm(std::vector<std::vector<char>>& grid_) : grid(grid_) {}

	//finds best path via path length and heuristic
	virtual void navigate(std::pair<int, int> startingPosition, std::pair<int, int>& moveTo) {}

	//returns vector of possible actions from a current position
	void returnActions(std::pair<int, int> currentPosition, std::vector<std::pair<int, int>>& actions);
protected:

	//mapped grid of players environment
	std::vector<std::vector<char>>& grid;
};

class AStar : public Algorithm {
public:
	AStar(std::vector<std::vector<char>>& grid_) : Algorithm(grid_) {}

	//finds best path via path length and heuristic
	//only works as a bfs for now
	void navigate(std::pair<int, int> startingPosition, std::pair<int, int>& moveTo) override;
};