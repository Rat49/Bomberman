#include "GameModule/Obstacle.hpp"
#include <random>
#include <unordered_set>

Obstacle::Obstacle(ObstacleType type, sf::Vector2i position, bool hasKeyOrGate) : obstacleType(type), obstaclePosition(position), obstacleHasKeyOrGate(hasKeyOrGate) {}

// Generate obstacles
std::vector<Obstacle> Obstacle::generateObstacles(int width, int height, int breakableCount, const sf::Vector2i& playerStartPosition)
{
	std::vector<Obstacle> obstacles;

	// Generate unbreakable obstacles on edges and at even positions
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			sf::Vector2i position(x, y);
			if (isValidUnbreakablePosition(position))
			{
				obstacles.emplace_back(ObstacleType::Unbreakable, position);
			}
		}
	}

	// Generates breakable obstacles in random places
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distX(1, width - 2);
	std::uniform_int_distribution<> distY(1, height - 2);

	std::unordered_set<std::pair<int, int>, std::hash<std::pair<int, int>>> usedPositions;

	// Add the starting position to the safety zone
	int safetyRadius = 2;
	for (int y = playerStartPosition.y - safetyRadius; y <= playerStartPosition.y + safetyRadius; ++y)
	{
		for (int x = playerStartPosition.x - safetyRadius; x <= playerStartPosition.x + safetyRadius; ++x)
		{
			if (x >= 0 && x < width && y >= 0 && y < height)
			{
				usedPositions.emplace(x, y);
			}
		}
	}

	int placedBreakables = 0;
	while (placedBreakables < breakableCount)
	{
		int x = distX(gen);
		int y = distY(gen);

		// Whether the field is free
		if (usedPositions.find({ x, y }) == usedPositions.end())
		{
			obstacles.emplace_back(ObstacleType::Breakable, sf::Vector2i(x, y));
			usedPositions.emplace(x, y);
			++placedBreakables;
		}
	}
	return obstacles;
}

sf::Vector2i Obstacle::getPosition() const
{
	return obstaclePosition;
}

ObstacleType Obstacle::getType() const
{
	return obstacleType;
}

bool Obstacle::hasKeyOrGate() const
{
	return obstacleHasKeyOrGate;
}

void Obstacle::setHasKeyOrGate(bool value)
{
	obstacleHasKeyOrGate = value;
}

bool Obstacle::isValidUnbreakablePosition(const sf::Vector2i& position)
{
	return (position.x % 2 == 0 && position.y % 2 == 0) || (position.x == 0 && position.y % 2 == 0) || (position.y == 0 && position.x % 2 == 0);
}
