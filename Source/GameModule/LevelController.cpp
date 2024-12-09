#include "GameModule/LevelController.hpp"
#include "Common/Logs.hpp"
#include "AssetManager/AssetManager.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "Common/Modules.hpp"
#include <set>
#include <utility>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>

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

LevelController::LevelController() : width(20), height(20), gameLevelType(GameLevelType::Easy), enemyCount(5), breakableCount(10), playerStartPosition(1, 1) {}

bool LevelController::Initialize(int32_t levelWidth, int32_t levelHeight, GameLevelType gameLevel, int32_t enemyCountNew, int32_t breakableCountNew, const sf::Vector2i& playerStartPositionNew, int32_t newNumOfBoosters)
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
	this->boostersNum = newNumOfBoosters;

	generateLevel(width, height, gameLevelType, enemyCount, breakableCount, playerStartPosition, newNumOfBoosters);

	return true;
}

void LevelController::generateLevel(int32_t newWidth, int32_t newHeight, GameLevelType gameLevel, int32_t enemyCountNew, int32_t breakableCountNew, const sf::Vector2i& playerStartPositionNew, int32_t newNumOfBoosters)
{
	if (!parseConfigFile(OBSTACLE_PATH))
	{
		LOG("Failed to parse file: $", OBSTACLE_PATH);
		return;
	}

	if (!parseConfigFile(ENEMY_PATH))
	{
		LOG("Failed to parse file: $", ENEMY_PATH);
		return;
	}

	if (!parseConfigFile(KEY_PATH))
	{
		LOG("Failed to parse file: $", KEY_PATH);
		return;
	}

	if (!parseConfigFile(GATE_PATH))
	{
		LOG("Failed to parse file: $", GATE_PATH);
		return;
	}

	if (!parseConfigFile(SPEED_BOOSTER_PATH))
	{
		LOG("Failed to parse file: $", SPEED_BOOSTER_PATH);
		return;
	}

	// Retrieve all walkable positions from the level
	const auto& walkablePos = Modules::Level->getWalkablePositions();
	freePositions.insert(freePositions.end(), walkablePos.begin(), walkablePos.end());

	this->width = newWidth;
	this->height = newHeight;
	this->gameLevelType = gameLevel;
	this->enemyCount = enemyCountNew;
	this->breakableCount = breakableCountNew;
	this->playerStartPosition = playerStartPositionNew;
	this->boostersNum = newNumOfBoosters;

	// Random number generator
	std::random_device rd;
	std::mt19937 gen(rd());

	// Generate all level components
	generateObstacles(gen);
	generateEnemies(gen);
	generateKeys(gen);
	generateGates(gen);
	generateBoosters(gen);
}

void LevelController::generateEnemies(std::mt19937& gen)
{
	// Generate a safety zone around the player to prevent placing obstacles too close
	std::set<std::pair<int32_t, int32_t>> usedPositions = generateSafetyZone();

	// Enemy types based on game level
	std::vector<EnemyType> availableTypes = getAvailableEnemyTypes(gameLevelType);

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
		if (placedEnemies >= enemyCount)
		{
			break;
		}

		// Extract the x and y coordinates from the current position
		int32_t x = static_cast<int32_t>(it->x);
		int32_t y = static_cast<int32_t>(it->y);

		// Generate patrolling points with busy check
		//std::vector<sf::Vector2i> patrollingPoints = generatePatrollingPoints(gen, sf::Vector2i(x, y), freePositions, enemyRange);

		// Increment the counter for placed enemy
		++placedEnemies;

		// Create a new enemy at the current position
		Enemy enemy(EnemyType::Basic, { (float)x, (float)y }); // , patrollingPoints);

		//load atlas texture
		m_atlasTexture = std::make_shared<sf::Texture>();
		m_atlasTexture = Modules::Assets->getTexture(m_atlasPath);

		// Define, load, assign and set the specific texture and set the position of the obstacle in the game world
		enemy.setTexture(*m_atlasTexture);
		enemy.setTextureRect(getTextureRect(ENEMY_RECT_NAME));
		enemy.setPosition((float)x, (float)y);

		// Add the enemy to the list of all enemies
		enemies.emplace_back(std::move(enemy));

		// Remove the used position from the free positions list
		it = freePositions.erase(it);
	}
}

void LevelController::draw(sf::RenderTarget& target) const
{
	for (const auto& enemy : enemies)
	{
		target.draw(*enemy.getCurrentAnimation());
	}

	for (const auto& key : keys)
	{
		target.draw(key);
	}

	for (const auto& gate : gates)
	{
		target.draw(gate);
	}

	for (const auto& booster : boosters)
	{
		target.draw(booster);
	}

	for (auto& obstacle : obstacles)
	{
		if (!obstacle.isExploded)
			target.draw(*obstacle.getCurrentAnimation());
	}
}

void LevelController::update(sf::RenderTarget& target)
{
	auto enemy_it = enemies.begin();
	while (enemy_it != enemies.end())
	{
		if (enemy_it->isDead())
		{
			enemy_it = enemies.erase(enemy_it);
		}
		else
		{
			++enemy_it;
		}
	}
	draw(target);
}

// Generate obstacles
void LevelController::generateObstacles(std::mt19937& gen)
{
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
		if (placedBreakables >= breakableCount)
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
		Obstacle obstacle(ObstacleType::Breakable, { it->x, it->y }, false);

		//load atlas texture
		//m_atlasTexture = std::make_shared<sf::Texture>();
		//m_atlasTexture = Modules::Assets->getTexture(m_atlasPath);

		// Define, load, assign and set the specific texture and set the position of the obstacle in the game world
		//obstacle.setTexture(*m_atlasTexture);
		//obstacle.setTextureRect(getTextureRect(OBSTACLE_RECT_NAME));
		//obstacle.setPosition((float)x, (float)y);

		// Save the obstacle's position in the breakable obstacles position vector
		breakableObstaclesPositions.emplace_back(obstacle.getPosition());

		// Add the obstacle to the list of all obstacles
		obstacles.emplace_back(std::move(obstacle));

		// Remove the used position from the free positions list
		it = freePositions.erase(it);
	}
}

bool LevelController::parseConfigFile(const std::string& configFilePath)
{
	Modules::Config->addFile(configFilePath); //"../../Data/Config/BreakableObstacle.ini");
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

sf::IntRect LevelController::getTextureRect(const std::string& textureName) const
{
	auto textureRect = m_texturesRect.find(textureName);

	if (textureRect != m_texturesRect.end())
	{
		return textureRect->second;
	}
	return sf::IntRect();
}

// Get available enemy types for the current level
std::vector<EnemyType> LevelController::getAvailableEnemyTypes(GameLevelType levelType) const
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
std::set<std::pair<int32_t, int32_t>> LevelController::generateSafetyZone() const
{
	std::set<std::pair<int32_t, int32_t>> safetyZone;

	safetyZone.insert(std::make_pair(64, 64));
	safetyZone.insert(std::make_pair(64, 128));
	safetyZone.insert(std::make_pair(128, 64));

	return safetyZone;
}

// Generate patrolling points
std::vector<sf::Vector2i> LevelController::generatePatrollingPoints(std::mt19937& gen, const sf::Vector2i& enemyPosition, std::vector<sf::Vector2f>& newFreePositions, int32_t range) const
{
	std::vector<sf::Vector2i> patrollingPoints;
	
	std::uniform_int_distribution<> distX(enemyPosition.x - range, enemyPosition.x + range);
	std::uniform_int_distribution<> distY(enemyPosition.y - range, enemyPosition.y + range);

	// Define a random distribution for the number of points between min and max
	std::uniform_int_distribution<> distNumPatrolPoints(minNumOfPatrolPoints, maxNumOfPatrolPoints);

	// Generate a random number of patrol points
	int32_t numPatrolPoints = distNumPatrolPoints(gen);

	int32_t maxAttempts = 10;
	int32_t attempts = 0;

	while (patrollingPoints.size() < numPatrolPoints && attempts < maxAttempts)
	{
		int32_t x = distX(gen);
		int32_t y = distY(gen);

		auto it = std::find_if(
			newFreePositions.begin(),
			newFreePositions.end(),
			[x, y](const sf::Vector2f& pos) {
				return static_cast<int32_t>(pos.x) == x && static_cast<int32_t>(pos.y) == y;
			});

		// Check if the position is free
		if (it != newFreePositions.end())
		{
			patrollingPoints.emplace_back(x, y);
		}
		++attempts;
	}
	return patrollingPoints;
}

void LevelController::generateGates(std::mt19937& gen)
{
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
		Gate gate({ x, y }, false, &keys[0]);

		//load atlas texture
		m_atlasTexture = std::make_shared<sf::Texture>();
		m_atlasTexture = Modules::Assets->getTexture(m_atlasPath);

		// Define, load, assign and set the specific texture and set the position of the obstacle in the game world
		gate.setTexture(*m_atlasTexture);
		gate.setTextureRect(getTextureRect(GATE_RECT_NAME));
		gate.setPosition((float)x, (float)y);

		// Add the gate to the list of all gates
		gates.emplace_back(std::move(gate));

		if (found != breakableObstaclesPositions.end())
		{
			// The gate is hidden under a brick
			gates.push_back({ sf::Vector2i(x, y), true, &keys[0] });

			it = breakableObstaclesPositions.erase(it);
		}
	}
}

void LevelController::generateKeys(std::mt19937& gen)
{
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
		Key key({ x, y });

		// Load atlas texture
		m_atlasTexture = std::make_shared<sf::Texture>();
		m_atlasTexture = Modules::Assets->getTexture(m_atlasPath);

		// Define, load, assign and set the specific texture and set the position of the key in the game world
		key.setTexture(*m_atlasTexture);
		key.setTextureRect(getTextureRect(KEY_RECT_NAME));
		key.setPosition((float)x, (float)y);

		// Add the gate to the list of all keys
		keys.emplace_back(std::move(key));

		if (found != breakableObstaclesPositions.end())
		{
			// The key is hidden under a brick
			keys.push_back({ sf::Vector2i(x, y) });

			it = breakableObstaclesPositions.erase(it);
		}
	}
}

void LevelController::generateBoosters(std::mt19937& gen)
{
	// Shuffle the remaining positions to randomize obstacle placement
	std::shuffle(breakableObstaclesPositions.begin(), breakableObstaclesPositions.end(), gen);

	// Iterate through the shuffled free positions
	for (auto it = breakableObstaclesPositions.begin(); it != breakableObstaclesPositions.end();)
	{
		// Stop if the required number of boosters have been placed
		if (boosters.size() >= boostersNum)
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

		Booster booster(BoosterType::Speed);

		// Load atlas texture
		m_atlasTexture = std::make_shared<sf::Texture>();
		m_atlasTexture = Modules::Assets->getTexture(m_atlasPath);

		// Define, load, assign and set the specific texture and set the position of the booster in the game world
		booster.setTexture(*m_atlasTexture);
		booster.setTextureRect(getTextureRect(SPEED_BOOSTER_RECT_NAME));
		booster.setPosition((float)x, (float)y);

		// Add the booster to the list of all gates
		boosters.emplace_back(std::move(booster));

		if (found != breakableObstaclesPositions.end())
		{
			// The booster is hidden under a brick
			 it = breakableObstaclesPositions.erase(it);
			
			boosters.push_back(BoosterType::Speed);
		}
	}
}

// Getter methods
std::vector<Obstacle>& LevelGenerator::getObstacles()
{
	return obstacles;
}

std::vector<Enemy>& LevelController::getEnemies()
{
	return enemies;
}

const std::vector<Gate>& LevelController::getGates() const
{
	return gates;
}

const std::vector<Booster>& LevelController::getBoosters() const
{
	return boosters;
}

const std::vector<Key>& LevelController::getKeys() const
{
	return keys;
}
