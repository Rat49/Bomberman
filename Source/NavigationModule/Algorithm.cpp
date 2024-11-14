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

		if (grid[tmpPosition.x][tmpPosition.y] != 1) {
			actions.push_back(tmpPosition);
		}

		tmpPosition = currentPosition;
	}
}

//returns position ai should move to to get closer to player
void Algorithm::moveTo(const sf::Vector2i& currentPosition, sf::Vector2i& moveToPosition) {
	std::vector<sf::Vector2i> actions;

	returnActions(currentPosition, actions);
	int closest = INT_MAX;
	for (auto& action : actions) {
		if (closest >= gridRelative[action.x][action.y]) {
			closest = gridRelative[action.x][action.y];
			moveToPosition = action;
		}
	}
}

//finds best path via path length and heuristic
//only works as a bfs for now
void AStar::navigate(const sf::Vector2i& startingPosition) {
	gridRelative = std::vector<std::vector<int>>(grid.size(), std::vector<int>(grid[0].size(), INT_MAX));
	//set of all visited positions
	std::unordered_set<sf::Vector2i, vector_hash> visited;

	//queue for bfs that stores position, path length
	std::queue<std::tuple<sf::Vector2i, int>> bfs;
	bfs.push({ startingPosition, //player starting position
				0 //player hasn't moved yet
		});

	std::vector<sf::Vector2i> legalActions;
	while (!bfs.empty()) {
		auto [position, pathLength] = bfs.front();
		bfs.pop();

		//if position wasn't visited before traverse it
		if (visited.find(position) == visited.end()) {
			visited.insert(position);
			returnActions(position, legalActions);

			gridRelative[position.x][position.y] = pathLength;
			for (auto& iter : legalActions) 
				bfs.push({ iter,pathLength + 1 });
		}
	}
}