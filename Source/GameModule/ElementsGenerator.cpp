#include "GameModule/ElementsGenerator.hpp"
#include "AssetManager/AssetManager.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "LevelHandlingModule/Level.hpp"
#include "LevelHandlingModule/LevelHandlingModule.hpp"
#include "GameModule/Gate.hpp"
#include "GameModule/Obstacle.hpp"
#include "GameModule/Key.hpp"
#include "GameModule/Booster.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"
#include <set>
#include <utility>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>
#include "EnemyFactory.hpp"

namespace
{
	const std::string X_COORDINATE = "x";
	const std::string Y_COORDINATE = "y";
	const std::string WIDTH = "width";
	const std::string HEIGHT = "height";
	const std::string ATLAS_PATH = "atlasPath";
	const std::string IS_LOOPING = "isLooping";
	const std::string RENDER_DURATION = "renderDuration";

	const std::string OBSTACLE_RECT_NAME = "BreakableObstacle1";
	const std::string OBSTACLE_PATH = "../../Data/Config/BreakableObstacle.ini";

	const std::string KEY_RECT_NAME = "Key1";
	const std::string KEY_PATH = "../../Data/Config/Key.ini";

	const std::string GATE_RECT_NAME = "Gate1";
	const std::string GATE_PATH = "../../Data/Config/Gate.ini";

	const std::string SPEED_BOOSTER_RECT_NAME = "SpeedUpBooster";
	const std::string SPEED_BOOSTER_PATH = "../../Data/Config/SpeedUpBooster.ini";

	const std::string ENEMY_RECT_NAME = "Enemy1";
	const std::string ENEMY_PATH = "../../Data/Config/Enemy1IdleAnimation.ini";
}

ElementsGenerator::ElementsGenerator() : m_levelConfig{ GameLevelType::Easy, 5, 10, 3 } {}


bool ElementsGenerator::initialize(const LevelConfigs& levelConfig)
{
  /*  enemyCountNew = 20;*/
	if (!parseConfigFile(OBSTACLE_PATH))
	{
		LOG("Failed to parse file: $", OBSTACLE_PATH);
		return false;
	}

	if (!parseConfigFile(ENEMY_PATH))
	{
		LOG("Failed to parse file: $", ENEMY_PATH);
		return false;
	}

	if (!parseConfigFile(KEY_PATH))
	{
		LOG("Failed to parse file: $", KEY_PATH);
		return false;
	}

	if (!parseConfigFile(GATE_PATH))
	{
		LOG("Failed to parse file: $", GATE_PATH);
		return false;
	}

	if (!parseConfigFile(SPEED_BOOSTER_PATH))
	{
		LOG("Failed to parse file: $", SPEED_BOOSTER_PATH);

		return false;
	}

	m_levelConfig = levelConfig;

	return true;
}

const GeneratedElements& ElementsGenerator::generateElements(const std::vector<sf::Vector2f>& walkablePositions, const sf::Texture& atlasTexture)
{
	//retrieve all walkable positions from the level
	freePositions.insert(freePositions.end(), walkablePositions.begin(), walkablePositions.end());

	//random number generator
	std::random_device rd;
	std::mt19937 gen(rd());

	//generate all level components
	m_generatedElements.obstacles	= generateObstacles(gen);
	m_generatedElements.keys		= generateKeys(gen, atlasTexture);
	m_generatedElements.enemies		= generateEnemies(gen);
	m_generatedElements.gates		= generateGates(gen, atlasTexture);
	m_generatedElements.boosters	= generateBoosters(gen, atlasTexture);

	return m_generatedElements;
}

// Generate obstacles
std::vector<std::shared_ptr<Obstacle>> ElementsGenerator::generateObstacles(std::mt19937& gen)
{
	//temp obstacles
	std::vector<std::shared_ptr<Obstacle>> obstacles;

	// Generate a safety zone around the player to prevent placing obstacles too close
	std::set<std::pair<int32_t, int32_t>> usedPositions = generateSafetyZone();

	// Remove positions that overlap with the safety zone
	freePositions.erase(std::remove_if(freePositions.begin(), freePositions.end(), [&usedPositions](const sf::Vector2f& pos)
		{
			int32_t x = static_cast<int32_t>(std::round(pos.x));
			int32_t y = static_cast<int32_t>(std::round(pos.y));
			std::pair<int32_t, int32_t> positionPair = std::make_pair(x, y);
			return usedPositions.find(positionPair) != usedPositions.end();
		}), freePositions.end());

	// Shuffle the remaining positions to randomize obstacle placement
	std::shuffle(freePositions.begin(), freePositions.end(), gen);

	// Counter to track how many breakable obstacles have been placed
	int32_t placedBreakables = 0;

	// Iterate through the shuffled free positions
	for (auto it = freePositions.begin(); it != freePositions.end();)
	{
		// Stop if the required number of breakable obstacles have been placed
		if (placedBreakables >= m_levelConfig.breakableCount)
		{
			break;
		}

		// Extract the x and y coordinates from the current position
		int32_t x = static_cast<int32_t>(it->x);
		int32_t y = static_cast<int32_t>(it->y);

		// Mark the position as used to avoid placing another obstacle here
		usedPositions.emplace(x, y);

		// Increment the counter for placed breakable obstacles
		++placedBreakables;

		// Create a new breakable obstacle at the current position
        auto obstacle = std::make_shared<Obstacle>(ObstacleType::Breakable, sf::Vector2f(it->x, it->y), false);

		// Save the obstacle's position in the breakable obstacles position vector
		breakableObstaclesPositions.emplace_back(obstacle->getPosition());

		// Add the obstacle to the list of all obstacles
		obstacles.push_back(obstacle);

		// Remove the used position from the free positions list
		it = freePositions.erase(it);
	}

	return obstacles;
}

std::vector<std::shared_ptr<Key>> ElementsGenerator::generateKeys(std::mt19937& gen, const sf::Texture& atlasTexture)
{
	//temp keys
	std::vector<std::shared_ptr<Key>> keys;

	// Shuffle the remaining positions to randomize obstacle placement
	std::shuffle(breakableObstaclesPositions.begin(), breakableObstaclesPositions.end(), gen);

	// Generate one key per level
	int32_t numKeys = 1;

	// Iterate through the shuffled free positions
	for (auto it = breakableObstaclesPositions.begin(); it != breakableObstaclesPositions.end();)
	{
		// Stop if the required number of keys have been placed
		if (keys.size() >= numKeys)
		{
			break;
		}

		// Extract the x and y coordinates from the current position
		int32_t x = static_cast<int32_t>(it->x);
		int32_t y = static_cast<int32_t>(it->y);

		// Check if the position is under a breakable object
		auto found = std::find_if(
			breakableObstaclesPositions.begin(),
			breakableObstaclesPositions.end(),
			[x, y](const sf::Vector2f& pos) {
				return static_cast<int32_t>(pos.x) == x && static_cast<int32_t>(pos.y) == y;
			});

		// Create a new key at the current position
        auto key = std::make_shared<Key>(sf::Vector2i(x, y));

		// Define, load, assign and set the specific texture and set the position of the key in the game world
		key->setTexture(atlasTexture);
		key->setTextureRect(getTextureRect(KEY_RECT_NAME));
		key->setPosition((float)x, (float)y);

		// Add the gate to the list of all keys
		keys.emplace_back((std::move(key)));

		if (found != breakableObstaclesPositions.end())
		{
			it = breakableObstaclesPositions.erase(it);
		}
	}

	return keys;
}

std::vector<std::shared_ptr<Gate>> ElementsGenerator::generateGates(std::mt19937& gen, const sf::Texture& atlasTexture)
{
	//temp gates
	std::vector<std::shared_ptr<Gate>> gates;

	// Shuffle the remaining positions to randomize obstacle placement
	std::shuffle(breakableObstaclesPositions.begin(), breakableObstaclesPositions.end(), gen);

	int32_t numGates = 1;

	// Iterate through the shuffled breakable obstacles positions
	for (auto it = breakableObstaclesPositions.begin(); it != breakableObstaclesPositions.end(); ++it)
	{
		// Stop if the required number of breakable obstacles have been placed
		if (gates.size() >= numGates)
		{
			break;
		}

		int32_t x = static_cast<int32_t>(it->x);
		int32_t y = static_cast<int32_t>(it->y);

		// Check if the position is under a breakable object
		auto found = std::find_if(
			breakableObstaclesPositions.begin(),
			breakableObstaclesPositions.end(),
			[x, y](const sf::Vector2f& pos) {
				return static_cast<int32_t>(pos.x) == x && static_cast<int32_t>(pos.y) == y;
			});

		// Create a new breakable obstacle at the current position
        auto gate = std::make_shared<Gate>(sf::Vector2i(x, y), false, m_generatedElements.keys[0]);

		// Define, load, assign and set the specific texture and set the position of the obstacle in the game world
		gate->setTexture(atlasTexture);
		gate->setTextureRect(getTextureRect(GATE_RECT_NAME));
		gate->setPosition((float)x, (float)y);

		// Add the gate to the list of all gates
		gates.emplace_back((std::move(gate)));

		if (found != breakableObstaclesPositions.end())
		{
			it = breakableObstaclesPositions.erase(it);
		}
	}

	return gates;
}

std::vector<std::shared_ptr<Booster>> ElementsGenerator::generateBoosters(std::mt19937& gen, const sf::Texture& atlasTexture)
{
	//temp boosters
	std::vector<std::shared_ptr<Booster>> boosters;

	// Shuffle the remaining positions to randomize obstacle placement
	std::shuffle(breakableObstaclesPositions.begin(), breakableObstaclesPositions.end(), gen);

	// Iterate through the shuffled free positions
	for (auto it = breakableObstaclesPositions.begin(); it != breakableObstaclesPositions.end();)
	{
		// Stop if the required number of boosters have been placed
		if (boosters.size() >= m_levelConfig.boostersCount)
		{
			break;
		}

		// Extract the x and y coordinates from the current position
		int32_t x = static_cast<int32_t>(it->x);
		int32_t y = static_cast<int32_t>(it->y);

		// Check if the position is under a obstacle
		auto found = std::find_if(
			breakableObstaclesPositions.begin(),
			breakableObstaclesPositions.end(),
			[x, y](const sf::Vector2f& pos) {
				return static_cast<int32_t>(pos.x) == x && static_cast<int32_t>(pos.y) == y;
			});

		auto booster = std::make_shared<Booster>(BoosterType::Speed);

		// Define, load, assign and set the specific texture and set the position of the booster in the game world
		booster->setTexture(atlasTexture);
		booster->setTextureRect(getTextureRect(SPEED_BOOSTER_RECT_NAME));
		booster->setPosition((float)x, (float)y);

		// Add the booster to the list of all gates
		boosters.emplace_back((std::move(booster)));

		if (found != breakableObstaclesPositions.end())
		{
			// The booster is hidden under a brick
			it = breakableObstaclesPositions.erase(it);
		}
	}

	return boosters;
}


std::vector <std::shared_ptr<EnemyBase>> ElementsGenerator::generateEnemies(std::mt19937& gen)
{
	//temp enemies
	std::vector<std::shared_ptr<EnemyBase>> enemies;

	// Generate a safety zone around the player to prevent placing obstacles too close
	std::set<std::pair<int32_t, int32_t>> usedPositions = generateSafetyZone();

	// Enemy types based on game level
	std::vector<EnemyType> availableTypes = getAvailableEnemyTypes(m_levelConfig.levelType);

	// Remove positions that overlap with the safety zone
	freePositions.erase(std::remove_if(freePositions.begin(), freePositions.end(), [&usedPositions](const sf::Vector2f& pos)
		{
			std::pair<int32_t, int32_t> positionPair = std::make_pair(static_cast<int32_t>(pos.x), static_cast<int32_t>(pos.y));
			return usedPositions.find(positionPair) != usedPositions.end();
		}), freePositions.end());

	// Shuffle the remaining positions to randomize obstacle placement
	std::shuffle(freePositions.begin(), freePositions.end(), gen);

	// Counter to track how many enemies have been placed
	int32_t placedEnemies = 0;

	// Iterate through the shuffled free positions
	for (auto it = freePositions.begin(); it != freePositions.end();)
	{
		// Stop if the required number of enemies have been placed
		if (placedEnemies >= m_levelConfig.enemyCount)
		{
			break;
		}

		// Extract the x and y coordinates from the current position
		int32_t x = static_cast<int32_t>(it->x);
		int32_t y = static_cast<int32_t>(it->y);

		// Increment the counter for placed enemy
		++placedEnemies;

		std::shared_ptr<EnemyBase> enemy = EnemyFactory::createEnemy(EnemyType::Basic, sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));

		// Add the enemy to the list of all enemies
		enemies.emplace_back((std::move(enemy)));

		// Remove the used position from the free positions list
		it = freePositions.erase(it);
	}

	return enemies;
}

bool ElementsGenerator::parseConfigFile(const std::string& configFilePath)
{
	Modules::Config->addFile(configFilePath);
	const ConfigFile& obstacleConfig = Modules::Config->getFile(configFilePath);

	bool anyTextureAdded = false;
	std::vector<std::string> m_configValues = { ATLAS_PATH, IS_LOOPING, RENDER_DURATION };
	std::vector<std::string> m_rectValues = { X_COORDINATE, Y_COORDINATE, WIDTH, HEIGHT };

	//check all sections
	const auto& sections = obstacleConfig.getAllSections();
	for (const auto& sectionName : sections)
	{

		if (!obstacleConfig.isSectionPresent(sectionName))
			break;

		if (obstacleConfig.getSection(sectionName).areValuesPresent(m_configValues))
		{
			const ConfigSection& mySection = obstacleConfig.getSection(sectionName);

			//load atlas path
			m_atlasPath = mySection.getValue(ATLAS_PATH).getString();

			//load isLooping value 
			m_isLooping = mySection.getValue(IS_LOOPING).getBool();

			//load render duration
			m_renderDuration = mySection.getValue(RENDER_DURATION).getFloat();

		}
		else if (obstacleConfig.getSection(sectionName).areValuesPresent(m_rectValues))
		{
			//load rect infos
			const ConfigSection& mySection = obstacleConfig.getSection(sectionName);
			int32_t xa = mySection.getValue(X_COORDINATE).getInt32();
			int32_t ya = mySection.getValue(Y_COORDINATE).getInt32();
			int32_t widtha = mySection.getValue(WIDTH).getInt32();
			int32_t heighta = mySection.getValue(HEIGHT).getInt32();

			//set to map
			m_texturesRect[sectionName] = sf::IntRect(xa, ya, widtha, heighta);
			anyTextureAdded = true;
		}
	}
	return anyTextureAdded;
}

sf::IntRect ElementsGenerator::getTextureRect(const std::string& textureName) const
{
	auto textureRect = m_texturesRect.find(textureName);

	if (textureRect != m_texturesRect.end())
	{
		return textureRect->second;
	}
	return sf::IntRect();
}

// Get available enemy types for the current level
std::vector<EnemyType> ElementsGenerator::getAvailableEnemyTypes(GameLevelType levelType) const
{
	switch (levelType)
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
std::set<std::pair<int32_t, int32_t>> ElementsGenerator::generateSafetyZone() const
{
	std::set<std::pair<int32_t, int32_t>> safetyZone;

	safetyZone.insert(std::make_pair(64, 64));
	safetyZone.insert(std::make_pair(64, 128));
	safetyZone.insert(std::make_pair(128, 64));

	return safetyZone;
}
