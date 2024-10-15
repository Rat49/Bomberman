#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>

class Algorithm {
public:
	Algorithm(std::vector<std::vector<bool>>& grid) : grid(grid) {}

	virtual ~Algorithm() {};

	//finds best path via path length and heuristic
	virtual void navigate(const sf::Vector2i& startingPosition,
		const sf::Vector2i& endPosition,
		sf::Vector2i& moveTo) = 0;

	//returns vector of possible actions from a current position
	void returnActions(const sf::Vector2i& currentPosition,
		const sf::Vector2i& playerPosition,
		std::vector<sf::Vector2i>& actions);
protected:

	//mapped grid of players environment
	std::vector<std::vector<bool>> grid;
};

class AStar : public Algorithm {
public:
	AStar(std::vector<std::vector<bool>>& grid) : Algorithm(grid) {}

	~AStar() {};

	//finds best path via path length and heuristic
	//only works as a bfs for now
	void navigate(const sf::Vector2i& startingPosition,
		const sf::Vector2i& endPosition,
		sf::Vector2i& moveTo) override;
};