#include "Algorithm.hpp"

//hash for pairs
struct pair_hash {
	template <class T1, class T2>
	std::size_t operator() (const std::pair<T1, T2>& pair) const {
		return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
	}
};

//returns vector of possible actions from a current position
void Algorithm::returnActions(std::pair<int, int> currentPosition, std::vector<std::pair<int, int>>& actions) {
	actions.clear();
	std::vector<std::pair<int, int>> directions = { {-1, 0},//up
													{1, 0},//down
													{0, 1},//right
													{0, -1} };//left

	//iterate over every direction and return only the possible ones
	std::pair<int, int> tmpPosition = currentPosition;
	for (auto& iter : directions) {
		tmpPosition.first += iter.first;
		tmpPosition.second += iter.second;

		if (grid[tmpPosition.first][tmpPosition.second] != 'O' &&
			grid[tmpPosition.first][tmpPosition.second] != 'P') {
			actions.push_back(tmpPosition);
		}

		tmpPosition = currentPosition;
	}
}

//finds best path via path length and heuristic
//only works as a bfs for now
void AStar::navigate(std::pair<int, int> startingPosition, std::pair<int, int>& moveTo) {
	//set of all visited positions
	std::unordered_set<std::pair<int, int>, pair_hash> visited;

	//queue for bfs that stores position, path length and a first action to that position
	std::queue<std::tuple<std::pair<int, int>, int, std::pair<int, int>>> bfs;
	bfs.push({ startingPosition, //player starting position
				0 ,  //player hasn't moved yet
				{0,0} }); // there is no direction yet

	std::vector<std::pair<int, int>> legalActions;
	while (!bfs.empty()) {
		auto [position, pathLength, direction] = bfs.front();
		bfs.pop();

		//if position wasn't visited before traverse it
		if (visited.find(position) == visited.end()) {
			visited.insert(position);
			returnActions(position, legalActions);

			for (auto& iter : legalActions) {
				if (pathLength == 0) {
					direction.first = iter.first - position.first;
					direction.second = iter.second - position.second;
				}
				if (grid[iter.first][iter.second] == 'E') {
					moveTo = direction;
					return;
				}
				bfs.push({ iter,pathLength + 1,direction });
			}
		}
	}
}