#include "GameModule/LevelGenerator.hpp"
#include "Common/Logs.hpp"
#include <set>
#include <utility>

LevelGenerator::LevelGenerator(int width, int height, int gameLevel, int enemyCount, int breakableCount, const sf::Vector2i& playerStartPosition)
	: width(width), height(height), gameLevel(gameLevel), enemyCount(enemyCount), breakableCount(breakableCount), playerStartPosition(playerStartPosition)
{
	if (width <= 2 || height <= 2)
	{
		LOG("Width and height must be greater than 2.");
	}

	if (enemyCount < 0)
	{
		LOG("Enemy count cannot be negative.");
	}

	if (breakableCount < 0)
	{
		LOG("Breakable count cannot be negative.");
	}

	if (playerStartPosition.x < 0 || playerStartPosition.x >= width || playerStartPosition.y < 0 || playerStartPosition.y >= height)
	{
		LOG("Player start position is out of bounds.");
	}
}

std::vector<Enemy> LevelGenerator::generateEnemies(const std::vector<Obstacle>& obstacles) const
{
	std::vector<Enemy> enemies;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distX(1, width - 2);
	std::uniform_int_distribution<> distY(1, height - 2);

	// Enemy types based on game level
	std::vector<EnemyType> availableTypes = getAvailableEnemyTypes(gameLevel);

	std::set<std::pair<int, int>> usedPositions = generateSafetyZone(playerStartPosition, 3);

	// Add obstacles to used positions
	for (const auto& obstacle : obstacles)
	{
		usedPositions.emplace(obstacle.getPosition().x, obstacle.getPosition().y);
	}

	int placedEnemies = 0;
	while (placedEnemies < enemyCount)
	{
		int x = distX(gen);
		int y = distY(gen);

		if (usedPositions.find({ x, y }) == usedPositions.end())
		{
			std::uniform_int_distribution<> distType(0, static_cast<int>(availableTypes.size() - 1));
			EnemyType type = availableTypes[distType(gen)];

			// Generate patrolling points with busy check
			std::vector<sf::Vector2i> patrollingPoints = generatePatrollingPoints(gen, usedPositions);

			// Add all patrol points to occupied positions
			for (const auto& point : patrollingPoints)
			{
				usedPositions.emplace(point.x, point.y);
			}

			enemies.emplace_back(type, sf::Vector2i(x, y), patrollingPoints);
			usedPositions.emplace(x, y);
			++placedEnemies;
		}
	}
	return enemies;
}

// Generate obstacles
std::vector<Obstacle> LevelGenerator::generateObstacles() const
{
	std::vector<Obstacle> obstacles;

	// Unbreakable obstacles
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			sf::Vector2i position(x, y);
			if (Obstacle::isValidUnbreakablePosition(position))
			{
				obstacles.emplace_back(ObstacleType::Unbreakable, position);
			}
		}
	}

	// Breakable obstacles
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distX(1, width - 2);
	std::uniform_int_distribution<> distY(1, height - 2);

	std::set<std::pair<int, int>> usedPositions = generateSafetyZone(playerStartPosition, 2);

	int totalAvailablePositions = (width - 2) * (height - 2) - static_cast<int>(usedPositions.size());

	// Check if enough obstacles can be generated
	if (breakableCount > totalAvailablePositions)
	{
		LOG("Not enough space to generate the requested number of breakable obstacles.");
	}

	int placedBreakables = 0;
	while (placedBreakables < breakableCount)
	{
		int x = distX(gen);
		int y = distY(gen);

		if (usedPositions.find({ x, y }) == usedPositions.end())
		{
			obstacles.emplace_back(ObstacleType::Breakable, sf::Vector2i(x, y));
			usedPositions.emplace(x, y);
			++placedBreakables;
		}
	}
	return obstacles;
}

// Get available enemy types for the current level
std::vector<EnemyType> LevelGenerator::getAvailableEnemyTypes(int level) const
{
	switch (level)
	{
	case 1: return { EnemyType::Basic };
	case 2: return { EnemyType::Basic, EnemyType::Speedy };
	case 3: return { EnemyType::Basic, EnemyType::Speedy, EnemyType::Chasing };
	case 4: return { EnemyType::Basic, EnemyType::Speedy, EnemyType::Chasing, EnemyType::BombThrower };
	case 5: return { EnemyType::Basic, EnemyType::Speedy, EnemyType::Chasing, EnemyType::BombThrower, EnemyType::Suicidal };
	default: return { EnemyType::Basic, EnemyType::Speedy, EnemyType::Chasing, EnemyType::BombThrower, EnemyType::Suicidal, EnemyType::Flying, EnemyType::Shielded };
	}
}

//Generate safety zone
std::set<std::pair<int, int>> LevelGenerator::generateSafetyZone(const sf::Vector2i& center, int radius) const
{
	std::set<std::pair<int, int>> safetyZone;
	for (int y = center.y - radius; y <= center.y + radius; ++y)
	{
		for (int x = center.x - radius; x <= center.x + radius; ++x)
		{
			if (x >= 0 && x < width && y >= 0 && y < height)
			{
				safetyZone.emplace(x, y);
			}
		}
	}
	return safetyZone;
}

// Generate patrolling points
std::vector<sf::Vector2i> LevelGenerator::generatePatrollingPoints(std::mt19937& gen, const std::set<std::pair<int, int>>& occupiedPositions) const
{
	std::set<std::pair<int, int>> localOccupiedPositions = occupiedPositions;
	std::vector<sf::Vector2i> patrollingPoints;
	std::uniform_int_distribution<> distX(1, width - 2);
	std::uniform_int_distribution<> distY(1, height - 2);

	while (patrollingPoints.size() < 3)
	{
		int x = distX(gen);
		int y = distY(gen);

		// Check if the position is free
		if (localOccupiedPositions.find({ x, y }) == localOccupiedPositions.end())
		{
			patrollingPoints.emplace_back(x, y);

			// Add the generated position to occupied
			localOccupiedPositions.insert({ x, y });
		}
	}
	return patrollingPoints;
}

void LevelGenerator::generateGates(std::mt19937& gen, std::set<std::pair<int, int>>& occupiedPositions)
{
	std::uniform_int_distribution<> distX(1, width - 2);
	std::uniform_int_distribution<> distY(1, height - 2);

	int numGates = 1;
	while (gates.size() < numGates)
	{
		int x = distX(gen);
		int y = distY(gen);

		// Check if the position is available
		if (occupiedPositions.find({ x, y }) == occupiedPositions.end())
		{
			// The gate is hidden under a brick
			gates.push_back({ sf::Vector2i(x, y), true });
			occupiedPositions.insert({ x, y });
		}
	}
}

void LevelGenerator::generateBoosters(std::mt19937& gen, std::set<std::pair<int, int>>& occupiedPositions, int numBoosters)
{
	std::uniform_int_distribution<> distX(1, width - 2);
	std::uniform_int_distribution<> distY(1, height - 2);
	std::vector<std::string> boosterTypes = { "speed", "bomb", "health" };

	while (boosters.size() < numBoosters)
	{
		int x = distX(gen);
		int y = distY(gen);

		if (occupiedPositions.find({ x, y }) == occupiedPositions.end())
		{
			std::string boosterType = boosterTypes[gen() % boosterTypes.size()];
			boosters.push_back({ sf::Vector2i(x, y), boosterType });
			occupiedPositions.insert({ x, y });
		}
	}
}
