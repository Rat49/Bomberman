#pragma once

#include "GameModule/Enemy.hpp"
#include "GameModule/Obstacle.hpp"
#include "GameModule/Booster.hpp"
#include "GameModule/Gate.hpp"
#include "GameModule/Key.hpp"
#include "LevelHandlingModule/Level.hpp"
#include <SFML/System.hpp>
#include <fstream>
#include <vector>
#include <random>
#include <set>

class LevelGenerator
{
public:
	LevelGenerator();

	bool Initialize(int levelWidth, int levelHeight, GameLevelType gameLevel, int enemyCountNew, int breakableCountNew, const sf::Vector2i& playerStartPositionNew);

	static LevelGenerator* generateLevel(int newWidth, int newHeight, GameLevelType gameLevel, int enemyCountNew, int breakableCountNew, const sf::Vector2i& playerStartPositionNew, int numBoosters);

	template <typename ObjectType>
	bool isObjectOnTile(const sf::Vector2i& tilePosition, const std::vector<ObjectType>& objects) const;
	
	// Getter methods for private members
	const std::vector<Obstacle>& getObstacles() const;
	const std::vector<Enemy>& getEnemies() const;
	const std::vector<Gate>& getGates() const;
	const std::vector<Key>& getKeys() const;
	const std::vector<Booster>& getBoosters() const;

	// A method for exporting layers to text files
	//void exportLevelToTextFiles(const std::string& prefix);

private:
	// Data members
	int width;
	int height;
	GameLevelType gameLevelType;
	int enemyCount;
	int breakableCount;
	sf::Vector2i playerStartPosition;

	int enemyRange = 3;
	int minNumOfPatrolPoints = 2;
	int maxNumOfPatrolPoints = 6;

	std::vector<Obstacle> obstacles;
	std::vector<Enemy> enemies;
	std::vector<Gate> gates;
	std::vector<Key> keys;
	std::vector<Booster> boosters;

	std::set<std::pair<int, int>> breakableObjPos;

	// Methods
	std::vector<EnemyType> getAvailableEnemyTypes(GameLevelType level) const;
	std::set<std::pair<int, int>> generateSafetyZone(const sf::Vector2i& center, int radius) const;
	std::vector<sf::Vector2i> generatePatrollingPoints(std::mt19937& gen, const sf::Vector2i& enemyPosition, const std::set<std::pair<int, int>>& occupiedPositions, int range) const;

	std::vector<std::vector<int>> generateLayer() const;

	void generateObstacles(std::vector<std::vector<int>>& layer, std::mt19937& gen);
	void generateEnemies(std::mt19937& gen);
	void generateGates(std::mt19937& gen);
	void generateKeys(std::mt19937& gen);
	void generateBoosters(std::mt19937& gen, int numBoosters);

	// A method for writing a layer to a file
	//void saveLayerToFile(const std::string& filename, const std::vector<std::vector<int>>& layer) const;
};

template <typename ObjectType>
bool LevelGenerator::isObjectOnTile(const sf::Vector2i& tilePosition, const std::vector<ObjectType>& objects) const
{
	for (const auto& object : objects)
	{
		if (object.getPosition() == tilePosition)
		{
			return true;
		}
	}
	return false;
}
