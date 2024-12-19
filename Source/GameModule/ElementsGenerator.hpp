#pragma once

#include "LevelHandlingModule/LevelShared.hpp"
#include "EnemyBase.hpp"
#include <SFML/System.hpp>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <random>
#include <set>

class Obstacle;
class Booster;
class Gate;
class Key;

class ElementsGenerator
{
public:

	ElementsGenerator();
	
	bool initialize(const LevelConfigs& levelConfig);

	const GeneratedElements& generateElements(const std::vector<sf::Vector2f>& walkablePositions, const sf::Texture& atlasTexture);

	template <typename ObjectType>
	bool isObjectOnTile(const sf::Vector2i& tilePosition, const std::vector<ObjectType>& objects) const;

private:

	//core functions for various level elements

	std::vector<std::shared_ptr<Obstacle>> generateObstacles(std::mt19937& gen);

	std::vector<std::shared_ptr<EnemyBase>> generateEnemies(std::mt19937& gen);
	
	std::vector<std::shared_ptr<Gate>> generateGates(std::mt19937& gen, const sf::Texture& atlasTexture);
	
	std::vector<std::shared_ptr<Key>> generateKeys(std::mt19937& gen, const sf::Texture& atlasTexture);
	
	std::vector<std::shared_ptr<Booster>> generateBoosters(std::mt19937& gen, const sf::Texture& atlasTexture);

	std::vector<EnemyType> getAvailableEnemyTypes(GameLevelType levelType) const;
	
	std::set<std::pair<int32_t, int32_t>> generateSafetyZone() const;

	sf::IntRect getTextureRect(const std::string& textureName) const;

	bool parseConfigFile(const std::string& configFilePath);
	
private:

	LevelConfigs m_levelConfig;

	GeneratedElements m_generatedElements;
    
	std::vector<sf::Vector2f> breakableObstaclesPositions;
	std::vector<sf::Vector2f> freePositions;
	std::set<std::pair<int32_t, int32_t>> safePositions;

	//parameters for enemy and patrol generation
	//int32_t enemyRange = 3;
	//int32_t minNumOfPatrolPoints = 2;
	//int32_t maxNumOfPatrolPoints = 6;

	std::string m_atlasPath;
	float m_renderDuration;
	bool m_isLooping;
	std::unordered_map<std::string, sf::IntRect> m_texturesRect;
};

template <typename ObjectType>
bool ElementsGenerator::isObjectOnTile(const sf::Vector2i& tilePosition, const std::vector<ObjectType>& objects) const
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
