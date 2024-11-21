#include "GameModule/LevelGenerator.hpp"
#include "Common/Logs.hpp"
#include <set>
#include <utility>

LevelGenerator::LevelGenerator() : width(20), height(20), gameLevelType(GameLevelType::Easy), enemyCount(5), breakableCount(10), playerStartPosition(1, 1) {}

bool LevelGenerator::Initialize(int levelWidth, int levelHeight, GameLevelType gameLevel, int enemyCountNew, int breakableCountNew, const sf::Vector2i& playerStartPositionNew)
{
	if (levelWidth <= 2 || levelHeight <= 2)
	{
		LOG("Width and height must be greater than 2.");
		return false;
	}

	if (enemyCountNew < 0)
	{
		LOG("Enemy count cannot be negative.");
		return false;
	}

	if (breakableCountNew < 0)
	{
		LOG("Breakable count cannot be negative.");
		return false;
	}

	if (playerStartPositionNew.x < 0 || playerStartPositionNew.x >= levelWidth || playerStartPositionNew.y < 0 || playerStartPositionNew.y >= levelHeight)
	{
		LOG("Player start position is out of bounds.");
		return false;
	}

	this->width = levelWidth;
	this->height = levelHeight;
	this->gameLevelType = gameLevel;
	this->enemyCount = enemyCountNew;
	this->breakableCount = breakableCountNew;
	this->playerStartPosition = playerStartPositionNew;

	return true;
}

LevelGenerator::LevelGenerator(int width, int height, GameLevelType gameLevel, int enemyCount, int breakableCount, const sf::Vector2i& playerStartPosition)
{
	Initialize(width, height, gameLevel, enemyCount, breakableCount, playerStartPosition);
}

void LevelGenerator::generateEnemies()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distX(1, width - 2);
	std::uniform_int_distribution<> distY(1, height - 2);

	// Enemy types based on game level
	std::vector<EnemyType> availableTypes = getAvailableEnemyTypes(gameLevelType);

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
}

// Generate obstacles
void LevelGenerator::generateObstacles()
{
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
			breakableObjPos.emplace(x, y);
			++placedBreakables;
		}
	}
}

// Get available enemy types for the current level
std::vector<EnemyType> LevelGenerator::getAvailableEnemyTypes(GameLevelType level) const
{
	switch (level)
	{
	case GameLevelType::Easy: 
		return { EnemyType::Basic };
	case GameLevelType::Medium: 
		return { EnemyType::Basic, EnemyType::Medium };
	case GameLevelType::Hard: 
		return { EnemyType::Basic, EnemyType::Medium, EnemyType::Hard };
	default: 
		return { EnemyType::Basic, EnemyType::Medium, EnemyType::Hard };
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

void LevelGenerator::generateGates(std::mt19937& gen) // , std::set<std::pair<int, int>>& occupiedPositions)
{
	std::uniform_int_distribution<> distX(1, width - 2);
	std::uniform_int_distribution<> distY(1, height - 2);

	int numGates = 1;
	while (gates.size() < numGates)
	{
		int x = distX(gen);
		int y = distY(gen);

		// Check if the position is under breakable object
		if (breakableObjPos.find({ x, y }) != breakableObjPos.end())
		{
			//Gate* newGate = new Gate(sf::Vector2i(x, y), true, &keys[0]);

			// The gate is hidden under a brick
			gates.push_back({ sf::Vector2i(x, y), true, &keys[0]});
			breakableObjPos.insert({ x, y });
		}
	}
}

void LevelGenerator::generateKeys(std::mt19937& gen) // , std::set<std::pair<int, int>>& occupiedPositions)
{
	std::uniform_int_distribution<> distX(1, width - 2);
	std::uniform_int_distribution<> distY(1, height - 2);

	// Generate one key per level
	int numKeys = 1; 
	while (keys.size() < numKeys)
	{
		int x = distX(gen);
		int y = distY(gen);

		// Checking if the position is under a breakable object
		if (breakableObjPos.find({ x, y }) == breakableObjPos.end())
		{
			// Add the key below the breakable object
			keys.push_back(Key(sf::Vector2i(x, y)));
			breakableObjPos.insert({ x, y });
		}
	}
}

void LevelGenerator::generateBoosters(std::mt19937& gen, int numBoosters)
{
	std::uniform_int_distribution<> distX(1, width - 2);
	std::uniform_int_distribution<> distY(1, height - 2);
	std::uniform_int_distribution<> distBoosterType(0, 2);

	for (int i = 0; i < numBoosters; ++i)
	{
		BoosterType boosterType = static_cast<BoosterType>(distBoosterType(gen));
		boosters.emplace_back(boosterType);
	}
}

// Getter methods
const std::vector<Obstacle>& LevelGenerator::getObstacles() const
{
	return obstacles;
}

const std::vector<Enemy>& LevelGenerator::getEnemies() const
{
	return enemies;
}

const std::vector<Gate>& LevelGenerator::getGates() const
{
	return gates;
}

const std::vector<Booster>& LevelGenerator::getBoosters() const
{
	return boosters;
}

const std::vector<Key>& LevelGenerator::getKeys() const
{
	return keys;
}
