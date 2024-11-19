#pragma once

#include "GameModule/Enemy.hpp"
#include "GameModule/Obstacle.hpp"
#include <SFML/System.hpp>
#include <vector>
#include <random>
#include <set>

struct Gate
{
	sf::Vector2i position;
	bool hiddenUnderBrick;
};

struct Booster
{
	sf::Vector2i position;
	std::string type;
};

class LevelGenerator
{
public:
	LevelGenerator(int width, int height, int gameLevel, int enemyCount, int breakableCount, const sf::Vector2i& playerStartPosition);

	std::vector<Enemy> generateEnemies(const std::vector<Obstacle>& obstacles) const;
	std::vector<Obstacle> generateObstacles() const;

	void generateGates(std::mt19937& gen, std::set<std::pair<int, int>>& occupiedPositions);
	void generateBoosters(std::mt19937& gen, std::set<std::pair<int, int>>& occupiedPositions, int numBoosters);

	std::vector<Gate> gates;
	std::vector<Booster> boosters;

private:
	// Data members
	int width;
	int height;
	int gameLevel;
	int enemyCount;
	int breakableCount;
	sf::Vector2i playerStartPosition;

	// Methods
	std::vector<EnemyType> getAvailableEnemyTypes(int level) const;
	std::set<std::pair<int, int>> generateSafetyZone(const sf::Vector2i& center, int radius) const;
	std::vector<sf::Vector2i> generatePatrollingPoints(std::mt19937& gen, const std::set<std::pair<int, int>>& occupiedPositions) const;
};
