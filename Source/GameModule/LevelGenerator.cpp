#include "GameModule/LevelGenerator.hpp"
#include "Common/Logs.hpp"
#include <set>
#include <utility>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>

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

void LevelGenerator::generateLevel(int newWidth, int newHeight, GameLevelType gameLevel, int enemyCountNew, int breakableCountNew, const sf::Vector2i& playerStartPositionNew, int numBoosters)
{
	// Set up the level parameters
	if (!Initialize(newWidth, newHeight, gameLevel, enemyCountNew, breakableCountNew, playerStartPositionNew))
	{
		LOG("Failed to initialize the level with provided parameters.");
		return;
	}

	// Random number generator
	std::random_device rd;
	std::mt19937 gen(rd());

	std::vector<std::vector<int>> layer = generateLayer();

	// Generate all level components
	generateObstacles(layer, gen);
	generateEnemies(gen);
	generateKeys(gen);
	generateGates(gen);
	generateBoosters(gen, numBoosters);

	saveLayerToFile("LevelTest_obstacles.txt", layer);
}

void LevelGenerator::generateEnemies(std::mt19937& gen)
{
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
			std::vector<sf::Vector2i> patrollingPoints = generatePatrollingPoints(gen, sf::Vector2i(x, y), usedPositions, enemyRadius);

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
void LevelGenerator::generateObstacles(std::vector<std::vector<int>>& layer, std::mt19937& gen)
{
	std::uniform_int_distribution<> distX(1, width - 2);
	std::uniform_int_distribution<> distY(1, height - 2);

	std::set<std::pair<int, int>> usedPositions = generateSafetyZone(playerStartPosition, 2);

	int totalAvailablePositions = (width - 2) * (height - 2) - static_cast<int>(usedPositions.size());

	if (breakableCount > totalAvailablePositions)
	{
		LOG("Not enough space to generate the requested number of breakable obstacles.");
	}

	int placedBreakables = 0;
	while (placedBreakables < breakableCount)
	{
		int x = distX(gen);
		int y = distY(gen);

		// Check if the position is free and transient (WALKABLE)
		if (usedPositions.find({ x, y }) == usedPositions.end() && layer[y][x] == 1)
		{
			// Set breakable field (BREAKABLE)
			layer[y][x] = 2;
			usedPositions.emplace(x, y);
			++placedBreakables;
		}
	}
}

std::vector<std::vector<int>> LevelGenerator::generateLayer() const
{
	// Make an empty layer with 1 (WALKABLE)
	std::vector<std::vector<int>> layer(height, std::vector<int>(width, 1));

	// Set outer walls as UNBREAKABLE
	for (int x = 0; x < width; ++x)
	{
		// Upper wall
		layer[0][x] = 0;
		// Lower wall
		layer[height - 1][x] = 0;
	}
	for (int y = 0; y < height; ++y)
	{
		// Left wall
		layer[y][0] = 0;
		// Right wall
		layer[y][width - 1] = 0;
	}

	// Add bulletproof fields inside the matrix
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			if (Obstacle::isValidUnbreakablePosition({ x, y }))
			{
				// UNBREAKABLE
				layer[y][x] = 0;
			}
		}
	}

	return layer;
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
std::vector<sf::Vector2i> LevelGenerator::generatePatrollingPoints(std::mt19937& gen, const sf::Vector2i& enemyPosition, const std::set<std::pair<int, int>>& occupiedPositions, int range) const
{
	std::set<std::pair<int, int>> localOccupiedPositions = occupiedPositions;
	std::vector<sf::Vector2i> patrollingPoints;
	std::uniform_int_distribution<> distX(enemyPosition.x - range, enemyPosition.x + range);
	std::uniform_int_distribution<> distY(enemyPosition.y - range, enemyPosition.y + range);

	while (patrollingPoints.size() <= range)
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

void LevelGenerator::generateGates(std::mt19937& gen)
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
			// The gate is hidden under a brick
			gates.push_back({ sf::Vector2i(x, y), true, &keys[0]});
			breakableObjPos.insert({ x, y });
		}
	}
}

void LevelGenerator::generateKeys(std::mt19937& gen)
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

// A method for exporting layers to text files
void LevelGenerator::exportLevelToTextFiles(const std::string& prefix)
{
	// Generating layer layers as a matrix
	std::vector<std::vector<int>> obstaclesLayer(width, std::vector<int>(height, 0));
	std::vector<std::vector<int>> boostersLayer(width, std::vector<int>(height, 0));
	std::vector<std::vector<int>> gatesLayer(width, std::vector<int>(height, 0));
	std::vector<std::vector<int>> enemiesLayer(width, std::vector<int>(height, 0));
	std::vector<std::vector<int>> keysLayer(width, std::vector<int>(height, 0));

	// Filling matrices with data from objects
	for (const auto& obstacle : obstacles)
	{
		obstaclesLayer[obstacle.getPosition().x][obstacle.getPosition().y] = 1;  // Obstacle = 1
	}

	for (const auto& booster : boosters)
	{
		boostersLayer[booster.getPosition().x][booster.getPosition().y] = 2;  // Booster = 2
	}

	for (const auto& gate : gates)
	{
		gatesLayer[gate.getGatePosition().x][gate.getGatePosition().y] = 3;  // Gate = 3
	}

	for (const auto& enemy : enemies)
	{
		enemiesLayer[enemy.getSpawnPosition().x][enemy.getSpawnPosition().y] = 4;  // Enemy = 4
	}

	for (const auto& key : keys)
	{
		keysLayer[key.getKeyPosition().x][key.getKeyPosition().y] = 5;  // Keys = 5
	}

	// Writing each layer to a text file
	//saveLayerToFile(prefix + "_obstacles.txt", obstaclesLayer);
	saveLayerToFile(prefix + "_boosters.txt", boostersLayer);
	saveLayerToFile(prefix + "_gates.txt", gatesLayer);
	saveLayerToFile(prefix + "_enemies.txt", enemiesLayer);
	saveLayerToFile(prefix + "_keys.txt", keysLayer);
}

// A method for writing a layer to a file
void LevelGenerator::saveLayerToFile(const std::string& filename, const std::vector<std::vector<int>>& layer) const
{
	// Define the path to the file
	const std::string directory = "C:\\Users\\dragana.djurdjevic\\sfml-bomberman\\Data\\Config";

	// Combine directory and file name
	std::filesystem::path fullPath = std::filesystem::path(directory) / filename;

	// Create directories if they do not exist
	std::filesystem::create_directories(fullPath.parent_path());

	// Try to open the file
	std::ofstream file(fullPath.string());

	if (file.is_open())
	{
		for (const auto& row : layer)
		{
			for (size_t i = 0; i < row.size(); ++i)
			{
				file << row[i] << (i < row.size() - 1 ? " " : "\n");
			}
		}
		file.close();
	}
	else
	{
		LOG("Failed to open file.");
		throw std::runtime_error("Failed to open file: " + filename);
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
