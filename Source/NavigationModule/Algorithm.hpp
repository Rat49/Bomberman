#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>

class Algorithm {
public:
	Algorithm(std::vector<std::vector<bool>>& grid) : grid(grid) {}

	virtual ~Algorithm() {};

	//finds best path via path length and heuristic
	virtual void navigate(const sf::Vector2i& startingPosition) = 0;

	//returns vector of possible actions from a current position
	void returnActions(const sf::Vector2i& currentPosition,
		std::vector<sf::Vector2i>& actions);

	//returns position ai should move to to get closer to player
	void moveTo(const sf::Vector2i& currentPosition, sf::Vector2i& moveToPosition);
protected:

	//mapped grid of players environment
	std::vector<std::vector<bool>> grid;

	//mapped grid of players relative position to any tile
	//smaller value == closer to player
	std::vector<std::vector<int>> gridRelative;
};

class AStar : public Algorithm {
public:
	AStar(std::vector<std::vector<bool>>& grid) : Algorithm(grid) {}

	~AStar() {};

	//finds best path via path length and heuristic
	//only works as a bfs for now
	void navigate(const sf::Vector2i& startingPosition) override;
};