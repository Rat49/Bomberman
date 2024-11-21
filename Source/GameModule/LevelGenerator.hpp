#pragma once

#include "GameModule/Enemy.hpp"
#include "GameModule/Obstacle.hpp"
#include "GameModule/Booster.hpp"
#include "GameModule/Gate.hpp"
#include "GameModule/Key.hpp"
#include "LevelHandlingModule/Level.hpp"
#include <SFML/System.hpp>
#include <vector>
#include <random>
#include <set>

class LevelGenerator
{
public:
	LevelGenerator();

	bool Initialize(int levelWidth, int levelHeight, GameLevelType gameLevel, int enemyCountNew, int breakableCountNew, const sf::Vector2i& playerStartPositionNew);

	LevelGenerator(int width, int height, GameLevelType gameLevel, int enemyCount, int breakableCount, const sf::Vector2i& playerStartPosition);

	void generateObstacles();
	void generateEnemies();
	void generateGates(std::mt19937& gen); // , std::set<std::pair<int, int>>& occupiedPositions);
	void generateKeys(std::mt19937& gen); // , std::set<std::pair<int, int>>& occupiedPositions);
	void generateBoosters(std::mt19937& gen, int numBoosters);

	// Getter methods for private members
	const std::vector<Obstacle>& getObstacles() const;
	const std::vector<Enemy>& getEnemies() const;
	const std::vector<Gate>& getGates() const;
	const std::vector<Key>& getKeys() const;
	const std::vector<Booster>& getBoosters() const;

private:
	// Data members
	int width;
	int height;
	GameLevelType gameLevelType;
	int enemyCount;
	int breakableCount;
	sf::Vector2i playerStartPosition;

	std::vector<Obstacle> obstacles;
	std::vector<Enemy> enemies;
	std::vector<Gate> gates;
	std::vector<Key> keys;
	std::vector<Booster> boosters;

	std::set<std::pair<int, int>> breakableObjPos;

	// Methods
	std::vector<EnemyType> getAvailableEnemyTypes(GameLevelType level) const;
	std::set<std::pair<int, int>> generateSafetyZone(const sf::Vector2i& center, int radius) const;
	std::vector<sf::Vector2i> generatePatrollingPoints(std::mt19937& gen, const std::set<std::pair<int, int>>& occupiedPositions) const;
};
