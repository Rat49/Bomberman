#pragma once

#include <SFML/System.hpp>
#include "GameModule/Enemy.hpp"
#include "GameModule/Obstacle.hpp"
#include "GameModule/Booster.hpp"
#include "GameModule/Gate.hpp"
#include "GameModule/Key.hpp"
#include "LevelHandlingModule/Level.hpp"
#include "LevelHandlingModule/LevelHandlingModule.hpp"
#include "LevelConfig.hpp"
#include <fstream>
#include <vector>
#include <random>
#include <set>

class LevelGenerator
{
public:
	LevelGenerator();

	bool Initialize(const LevelConfig& levelConfig);

	void generateLevel(const LevelConfig& levelConfig);

	void draw(sf::RenderTarget& target) const;
	
	// Getter methods for private members
	const std::vector<Obstacle>& getObstacles() const;
	const std::vector<Enemy>& getEnemies() const;
	const std::vector<Gate>& getGates() const;
	const std::vector<Key>& getKeys() const;
	const std::vector<Booster>& getBoosters() const;

	template <typename ObjectType>
	bool isObjectOnTile(const sf::Vector2i& tilePosition, const std::vector<ObjectType>& objects) const;

private:

	// Variables
	LevelConfig m_levelConfig;

	int32_t enemyRange = 3;
	int32_t minNumOfPatrolPoints = 2;
	int32_t maxNumOfPatrolPoints = 6;

	std::vector<Obstacle> obstacles;
	std::vector<Enemy> enemies;
	std::vector<Gate> gates;
	std::vector<Key> keys;
	std::vector<Booster> boosters;

	std::vector<sf::Vector2f> breakableObstaclesPositions;
	std::vector<sf::Vector2f> freePositions;
	std::set<std::pair<int32_t, int32_t>> safePositions;

	std::string m_atlasPath;
	float m_renderDuration;
	bool m_isLooping;

	std::shared_ptr<sf::Texture> m_atlasTexture;
	std::unordered_map<std::string, sf::IntRect> m_texturesRect;

	// Methods
	std::vector<EnemyType> getAvailableEnemyTypes(GameLevelType levelType) const;
	std::set<std::pair<int32_t, int32_t>> generateSafetyZone() const;
	std::vector<sf::Vector2i> generatePatrollingPoints(std::mt19937& gen, const sf::Vector2i& enemyPosition, std::vector<sf::Vector2f>& newFreePositions, int32_t range) const;

	void generateObstacles(std::mt19937& gen);
	void generateEnemies(std::mt19937& gen);
	void generateGates(std::mt19937& gen);
	void generateKeys(std::mt19937& gen);
	void generateBoosters(std::mt19937& gen);

	sf::IntRect getTextureRect(const std::string& textureName) const;
	bool parseConfigFile(const std::string& configFilePath);
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
