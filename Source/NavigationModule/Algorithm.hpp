#pragma once

#include <vector>
#include <utility>

class Algorithm {
public:
	Algorithm(std::vector<std::vector<char>>& grid) : grid(grid) {}

	virtual ~Algorithm() {};

	//finds best path via path length and heuristic
	virtual void navigate(std::pair<int, int> startingPosition, std::pair<int, int>& moveTo) = 0;

	//returns vector of possible actions from a current position
	void returnActions(std::pair<int, int> currentPosition, std::vector<std::pair<int, int>>& actions);
protected:

	//mapped grid of players environment
	std::vector<std::vector<char>>& grid;
};

class AStar : public Algorithm {
public:
	AStar(std::vector<std::vector<char>>& grid) : Algorithm(grid) {}

	~AStar() {};

	//finds best path via path length and heuristic
	//only works as a bfs for now
	void navigate(std::pair<int, int> startingPosition, std::pair<int, int>& moveTo) override;
};