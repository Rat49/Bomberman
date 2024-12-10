#pragma once

#include <SFML/System.hpp>
#include "GameModule/Enemy.hpp"
#include "GameModule/Obstacle.hpp"
#include "GameModule/Booster.hpp"
#include "GameModule/Gate.hpp"
#include "GameModule/Key.hpp"
#include "LevelHandlingModule/Level.hpp"
#include "LevelHandlingModule/LevelHandlingModule.hpp"
#include <fstream>
#include <vector>
#include <random>
#include <set>

class LevelController
{
public:
	LevelController();

	bool Initialize(int32_t levelWidth, int32_t levelHeight, GameLevelType gameLevel, int32_t enemyCountNew, int32_t breakableCountNew, const sf::Vector2i& playerStartPositionNew, int32_t newNumOfBoosters);

	void generateLevel(int32_t newWidth, int32_t newHeight, GameLevelType gameLevel, int32_t enemyCountNew, int32_t breakableCountNew, const sf::Vector2i& playerStartPositionNew, int32_t newNumOfBoosters);

	void update(sf::RenderTarget& target);
	
	// Getter methods for private members
	//std::vector<Obstacle>& getObstacles();
	std::list<std::shared_ptr<Obstacle>>& getObstacles();
	std::list<std::shared_ptr<Enemy>>& getEnemies();
	std::list<std::shared_ptr<Gate>>& getGates();
	std::list<std::shared_ptr<Key>>& getKeys();
	std::list<std::shared_ptr<Booster>>& getBoosters();

	template <typename ObjectType>
	bool isObjectOnTile(const sf::Vector2i& tilePosition, const std::vector<ObjectType>& objects) const;

private:
	// Variables
	int32_t width;
	int32_t height;
	GameLevelType gameLevelType;
	int32_t enemyCount;
	int32_t breakableCount;
	int32_t boostersNum;
	sf::Vector2i playerStartPosition;

	int32_t enemyRange = 3;
	int32_t minNumOfPatrolPoints = 2;
	int32_t maxNumOfPatrolPoints = 6;

	//std::vector<Obstacle> obstacles;
	std::list<std::shared_ptr<Obstacle>> obstacles;
	std::list<std::shared_ptr<Enemy>> enemies;
	std::list<std::shared_ptr<Gate>> gates;
	std::list<std::shared_ptr<Key>> keys;
	std::list<std::shared_ptr<Booster>> boosters;

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

	void draw(sf::RenderTarget& target);

	void generateObstacles(std::mt19937& gen);
	void generateEnemies(std::mt19937& gen);
	void generateGates(std::mt19937& gen);
	void generateKeys(std::mt19937& gen);
	void generateBoosters(std::mt19937& gen);

	sf::IntRect getTextureRect(const std::string& textureName) const;
	bool parseConfigFile(const std::string& configFilePath);
};

template <typename ObjectType>
bool LevelController::isObjectOnTile(const sf::Vector2i& tilePosition, const std::vector<ObjectType>& objects) const
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
