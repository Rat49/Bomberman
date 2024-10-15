#include "Algorithm.hpp"
#include <functional> 
#include <unordered_set>
#include <unordered_map>
#include <queue>

//hash for sf::Vector2i
struct vector_hash {
	std::size_t operator() (const sf::Vector2i& vec) const {
		return std::hash<int>()(vec.x) ^ std::hash<int>()(vec.y);
	}
};

//returns vector of possible actions from a current position
void Algorithm::returnActions(const sf::Vector2i& currentPosition,
							const sf::Vector2i& playerPosition,
							std::vector<sf::Vector2i>& actions) {
	actions.clear();
	std::vector<sf::Vector2i> directions = { {-1, 0},//up
											{1, 0},//down
											{0, 1},//right
											{0, -1} };//left

	//iterate over every direction and return only the possible ones
	sf::Vector2i tmpPosition = currentPosition;
	for (auto& iter : directions) {
		tmpPosition.x += iter.x;
		tmpPosition.y += iter.y;

		if (grid[tmpPosition.x][tmpPosition.y] != 1 &&
			tmpPosition != playerPosition) {
			actions.push_back(tmpPosition);
		}

		tmpPosition = currentPosition;
	}
}

//finds best path via path length and heuristic
//only works as a bfs for now
void AStar::navigate(const sf::Vector2i& startingPosition,
	const sf::Vector2i& endPosition,
	sf::Vector2i& moveTo) {
	//set of all visited positions
	std::unordered_set<sf::Vector2i, vector_hash> visited;

	//queue for bfs that stores position, path length and a first action to that position
	std::queue<std::tuple<sf::Vector2i, int, sf::Vector2i>> bfs;
	bfs.push({ startingPosition, //player starting position
				0 ,  //player hasn't moved yet
				{0,0} }); // there is no direction yet

	std::vector<sf::Vector2i> legalActions;
	while (!bfs.empty()) {
		auto [position, pathLength, direction] = bfs.front();
		bfs.pop();

		//if position wasn't visited before traverse it
		if (visited.find(position) == visited.end()) {
			visited.insert(position);
			returnActions(position, startingPosition, legalActions);

			for (auto& iter : legalActions) {
				if (pathLength == 0) {
					direction.x = iter.x - position.x;
					direction.y = iter.y - position.y;
				}
				if (iter == endPosition) {
					moveTo = direction;
					return;
				}
				bfs.push({ iter,pathLength + 1,direction });
			}
		}
	}
}