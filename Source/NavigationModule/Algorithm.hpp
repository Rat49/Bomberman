#pragma once

#include <vector>
#include <utility>

class Algorithm {
public:
	Algorithm(std::vector<std::vector<bool>>& grid) : grid(grid) {}

	virtual ~Algorithm() {};

	//finds best path via path length and heuristic
	virtual void navigate(const std::pair<int, int>& startingPosition,
		const std::pair<int, int>& endPosition,
		std::pair<int, int>& moveTo) = 0;

	//returns vector of possible actions from a current position
	void returnActions(const std::pair<int, int>& currentPosition,
		const std::pair<int, int>& endPosition,
		std::vector<std::pair<int, int>>& actions);
protected:

	//mapped grid of players environment
	std::vector<std::vector<bool>>& grid;
};

class AStar : public Algorithm {
public:
	AStar(std::vector<std::vector<bool>>& grid) : Algorithm(grid) {}

	~AStar() {};

	//finds best path via path length and heuristic
	//only works as a bfs for now
	void navigate(const std::pair<int, int>& startingPosition,
		const std::pair<int, int>& playerPosition,
		std::pair<int, int>& moveTo) override;
};