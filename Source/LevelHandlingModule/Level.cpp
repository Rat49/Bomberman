#include "Level.hpp"
#include "AssetManager/AssetManager.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "GameModule/ElementsGenerator.hpp"
#include "GameModule/GameModule.hpp"
#include "GameModule/Gate.hpp"
#include "GameModule/Obstacle.hpp"
#include "GameModule/UnbreakableObstacle.hpp"
#include "GameModule/Key.hpp"
#include "GameModule/EnemyBase.hpp"
#include "GameModule/Booster.hpp"
#include "Common/Modules.hpp"
#include "SFML/Graphics.hpp"
#include <Common/Logs.hpp>
#include "LevelData.hpp"
#include "Tile.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

#include "Common/Logs.hpp"

namespace
{
	//atlas
	const std::string ID = "id";
	const std::string X_COORD = "x";
	const std::string Y_COORD = "y";
	const std::string ATLAS_PATH = "Game/Textures/levelAtlas.png";
	const int8_t ATLAS_SPRITE_SIZE = 64;

	//levelConfig
	const std::string ID_CONFIG = "id";
	const std::string LEVEL_TYPE = "levelType";
	const std::string ENEMY_COUNT = "enemyCount";
	const std::string BREAKABLE_COUNT = "breakableCount";
	const std::string BOOSTERS_COUNT = "boostersCount";

	const int32_t numberOfTilesWidth = 14;	// number of tiles by width that player can see in one moment
	const int32_t numberOfTilesHeight = 11;	// 16 x 13 in the original game

	//const std::string UNBREAKABLE_OBSTACLE = "Undestroyable";
    //const std::string WALKABLE_TILE = "Walkable";
    } // namespace

Level::Level(const std::string baseLevelConfigPath)
	:m_configPath(baseLevelConfigPath)
{}

bool Level::initialize()
{
	//load level configuration data
	if (!m_levelData.loadLevelConfigData(m_configPath))
	{
		LOG("Failed to load level data from: " + m_configPath);
		return false;
	}

	//load tileSet configuration data (tileTypes)
	if (!m_levelData.loadTilesetConfigData(m_levelData.getTilesetPath()))
	{
		LOG("Failed to load tileSet data from : " + m_levelData.getTilesetPath());
		return false;
	}

	//initialize level tiles based on tile IDs
	if (!loadTiles())
	{
		LOG("Failed to load tiles for the level");
		return false;
	}

	//initialize level tiles based on tile IDs
	if (!loadLevel(m_levelData.getLevelPath()))
	{
		LOG("Failed to load level from : " + m_levelData.getLevelPath());
		return false;
	}

	//initialize levelElementsConfig for generating elements on level
	if (!loadConfig(m_levelData.getLevelElementsConfigPath()))
	{
		LOG("Failed to load level config from file [$]:", m_levelData.getLevelElementsConfigPath());
		return false;
	}

    // Setting view to be defined size
    sf::Vector2f viewSize(numberOfTilesWidth * ATLAS_SPRITE_SIZE, numberOfTilesHeight * ATLAS_SPRITE_SIZE);
    m_view.setSize(viewSize);

	return true;
}


bool Level::loadTiles() 
{
	m_atlasTexture = Modules::Assets->getTexture(ATLAS_PATH);

	Modules::Config->addFile(m_levelData.getTilesetAssetConfigPath());
	const ConfigFile& tileTexturesSettings = Modules::Config->getFile(m_levelData.getTilesetAssetConfigPath());
	const auto& sections = tileTexturesSettings.getAllSections();

	for (const auto& section : sections)
	{
		int32_t id = tileTexturesSettings.getSection(section).getValue(ID).getInt32();
		int32_t x = tileTexturesSettings.getSection(section).getValue(X_COORD).getInt32();
		int32_t y = tileTexturesSettings.getSection(section).getValue(Y_COORD).getInt32();

		Tile newTile;
		sf::IntRect newRect(x, y, ATLAS_SPRITE_SIZE, ATLAS_SPRITE_SIZE);
		newTile.initialize(id, newRect, m_atlasTexture);
		m_availableTiles.emplace(id, std::make_shared<Tile>(newTile));
		if (!m_availableTiles[id])
		{
			return false;
		}
	}

	return true;
}


bool Level::loadLevel(const std::string& levelPath)
{
	//use Asset Manager to get level file data
	const auto levelData = Modules::Assets->getLevel(levelPath);

	if (levelData->empty())
	{
		LOG("Failed to load level .csv file from [$]", levelPath);
		return false;
	}

	//convert data in string stream
	std::string levelString(levelData->begin(), levelData->end());
	std::istringstream file(levelString);

	//read each line of file
	int32_t row = 0;
	std::string line;
	while (std::getline(file, line))
	{
		std::vector<FieldInfo> tileRow;
		std::stringstream sStream(line);
		std::string value;
		int32_t col = 0;

		//read row value
		while (std::getline(sStream, value, ','))
		{
			int32_t tempId = std::stoi(value);
			
			FieldInfo newFieldInfo;
			newFieldInfo.tile = m_availableTiles[tempId];
			newFieldInfo.tilePosition = { (float)(col * m_levelData.getTileWidth()), (float)(row * m_levelData.getTileHeight()) };
			tileRow.push_back(newFieldInfo);
			++col;
		}

		m_fields.push_back(tileRow);
		++row;
	}

	return true;
}

bool Level::loadConfig(const std::string levelConfigPath)
{
	//init config file
	Modules::Config->addFile(levelConfigPath);
	const ConfigFile& LevelManagerFile = Modules::Config->getFile(levelConfigPath);

	bool valuesFound = false;
	std::vector<std::string> configNames = { ID_CONFIG, LEVEL_TYPE, ENEMY_COUNT, BREAKABLE_COUNT, BOOSTERS_COUNT };

	//check all sections
	const auto& sections = LevelManagerFile.getAllSections();
	for (const auto& sectionName : sections)
	{

		if (!LevelManagerFile.isSectionPresent(sectionName))
			break;

		if (LevelManagerFile.getSection(sectionName).areValuesPresent(configNames))
		{
			const ConfigSection& mySection = LevelManagerFile.getSection(sectionName);

			//store values in map
			m_levelConfig.levelType = static_cast<GameLevelType>(mySection.getValue(LEVEL_TYPE).getInt32());
			m_levelConfig.enemyCount = mySection.getValue(ENEMY_COUNT).getInt32();
			m_levelConfig.breakableCount = mySection.getValue(BREAKABLE_COUNT).getInt32();
			m_levelConfig.boostersCount = mySection.getValue(BOOSTERS_COUNT).getInt32();

			m_levelConfigData[mySection.getValue(ID_CONFIG).getInt32()] = m_levelConfig;

			valuesFound = true;
		}
	}

	return valuesFound;
}

bool Level::setUpElements(int32_t levelElementsId)
{
	auto it = m_levelConfigData.find(levelElementsId);
	if (it == m_levelConfigData.end())
	{
		LOG("Level with id [$] not found (not initialized from file).", levelElementsId);
		return false;
	}

	//walkable positions
	const std::vector<sf::Vector2f>& walkablePositions = getWalkablePositions();

	initializeUnbreakableObstacle();

	//initialize elements generator
	m_elementsGenerator = std::make_unique<ElementsGenerator>();
	if (!m_elementsGenerator->initialize(it->second))
	{
		LOG("Failed to initialize elements generator with id [$]" , levelElementsId);
		return false;
	}

	//generate elements
	const auto& generatedElements = m_elementsGenerator->generateElements(walkablePositions, *m_atlasTexture);

	//store generated elements on level
	addObstacles(generatedElements.obstacles);
	addKeys(generatedElements.keys);
	addGates(generatedElements.gates);
	addBoosters(generatedElements.boosters);
    addEnemies(generatedElements.enemies);
    m_generatedElements.navGrid = generatedElements.navGrid;

	return true;
}

void Level::initializeUnbreakableObstacle()
{
    const std::vector<sf::Vector2f>& unbreakablePositions = getUnbreakableObstaclePositions();

    for (const auto& position : unbreakablePositions)
    {
        auto collisionObject = std::make_unique<UnbreakableObstacle>(position, sf::Vector2f(unbreakableObstacleCollisionSize, unbreakableObstacleCollisionSize));

		m_generatedElements.unbreakableObstacles.push_back(std::move(collisionObject));
    }
}

void Level::addObstacles(const std::vector<std::shared_ptr<Obstacle>>& obstacles)
{
	for (const auto& obstacle : obstacles)
	{
		m_generatedElements.obstacles.push_back(obstacle);
	}
}

void Level::addEnemies(const std::vector<std::shared_ptr<EnemyBase>>& enemies)
{
	for (const auto& enemy : enemies)
	{
		m_generatedElements.enemies.push_back(enemy);
	}
}

void Level::addGates(const std::vector<std::shared_ptr<Gate>>& gates)
{
	for (const auto& gate : gates)
	{
		m_generatedElements.gates.push_back(gate);
	}
}

void Level::addKeys(const std::vector<std::shared_ptr<Key>>& keys)
{
	for (const auto& key : keys)
	{
		m_generatedElements.keys.push_back(key);
	}
}

void Level::addBoosters(const std::vector<std::shared_ptr<Booster>>& boosters)
{
	for (const auto& booster : boosters)
	{
		m_generatedElements.boosters.push_back(booster);
	}
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.setView(m_view);
    const auto& center = m_view.getCenter();
    const auto& size   = m_view.getSize();

    const float halfWidth  = size.x / 2.f;
    const float halfHeight = size.y / 2.f;

    // getting all edges of view
    const float viewLeft   = center.x - halfWidth;
    const float viewTop    = center.y - halfHeight;
    const float viewRight  = center.x + halfWidth;
    const float viewBottom = center.y + halfHeight;

    // getting visible tile range
    auto startRow = std::max(0, static_cast<int>(viewTop / ATLAS_SPRITE_SIZE));
    auto endRow   = std::min(m_fields.size(), static_cast<std::size_t>(viewBottom / ATLAS_SPRITE_SIZE) + 1);

    auto startCol = std::max(0, static_cast<int>(viewLeft / ATLAS_SPRITE_SIZE));
    auto endCol   = std::min(m_fields[0].size(), static_cast<std::size_t>(viewRight / ATLAS_SPRITE_SIZE) + 1);

    // iterating only through visible tiles
    for (auto row = startRow; row < endRow; ++row)
    {
        for (auto col = startCol; col < endCol; ++col)
        {
            const FieldInfo& fieldInfo = m_fields[row][col];

            Tile drawableTile = *fieldInfo.tile;
            drawableTile.setPosition(fieldInfo.tilePosition);

            target.draw(drawableTile, states);
        }
    }

	for (const auto& key : m_generatedElements.keys)
	{
		target.draw(*key, states);
	}

	for (const auto& gate: m_generatedElements.gates)
	{
		target.draw(*gate, states);
	}
	
	for (const auto& booster : m_generatedElements.boosters)
    {
        target.draw(*booster, states);
        target.draw(booster->getCollisionBox().getRectangle(), states);
    }

	for (const auto& obstacle : m_generatedElements.obstacles)
	{
        target.draw(*obstacle->getCurrentAnimation(), states);
	}

	for (const auto& enemy : m_generatedElements.enemies)
	{
        target.draw(*enemy->getCurrentAnimation(), states);
	}	
}

void Level::update(sf::RenderWindow* window, float deltaTime)
{
    auto boostersIterator = m_generatedElements.boosters.begin();
    while (boostersIterator != m_generatedElements.boosters.end())
    {
        if ((*boostersIterator)->getIsPickedUp())
        {
            Modules::Physics->deleteObject(&(*boostersIterator)->getCollisionBox());
            (*boostersIterator)->emitCallback();
            boostersIterator = m_generatedElements.boosters.erase(boostersIterator);
        }
        else
        {
            ++boostersIterator;
        }
    }

    auto enemy_it = m_generatedElements.enemies.begin();
	while (enemy_it != m_generatedElements.enemies.end())
	{
        auto* enemy = enemy_it->get();
        enemy->getAIController().fsm->Update();
        enemy->updateVelocity(deltaTime);
        if (enemy->isDead())
        {
            enemy_it = m_generatedElements.enemies.erase(enemy_it);
        }
        else
        {
            ++enemy_it;
        }
	}
	
	auto obstacle_it = m_generatedElements.obstacles.begin();
	while (obstacle_it != m_generatedElements.obstacles.end())
	{
        auto* obstacle = obstacle_it->get();
		if (obstacle->hasExploded())
		{
            Modules::Physics->deleteObject(&obstacle->getCollisionBox());
            sf::Vector2i gridPos = static_cast<sf::Vector2i>(obstacle->getCollisionBox().getCenter()) / 64;
            (*m_generatedElements.navGrid)[gridPos.y][gridPos.x] = 0;
            obstacle_it = m_generatedElements.obstacles.erase(obstacle_it);
		}
		else
		{
            ++obstacle_it;
		}
	}

	//for (int i = 0; i < m_generatedElements.navGrid->size(); ++i)
	//{
	//	for (int j = 0; j < (*m_generatedElements.navGrid)[0].size(); ++j)
	//	{
 //           std::cout << (*m_generatedElements.navGrid)[i][j];
	//	}
 //       std::cout << std::endl;
	//}

	//system("cls");

	draw(*window, sf::RenderStates::Default);
}

void Level::setViewOffset(const sf::Vector2f& offset, const sf::RenderWindow& window)
{
    //calculate the total level width and height in pixels
    float levelPixelWidth  = static_cast<float>(m_fields[0].size() * m_levelData.getTileWidth());
    float levelPixelHeight = static_cast<float>(m_fields.size() * m_levelData.getTileHeight());

    //initialize view center to the target offset position
    sf::Vector2f viewCenter = offset;

    //define minimum and maximum bounds
    float minX = m_view.getSize().x / 2.f;
    float maxX = std::max(levelPixelWidth - m_view.getSize().x / 2.f, minX);
    float minY = m_view.getSize().y / 2.f;
    float maxY = std::max(levelPixelHeight - m_view.getSize().y / 2.f, minY);

    //clamp the view center coordinates to ensure they remain within level bounds
    viewCenter.x = std::clamp(viewCenter.x, minX, maxX);
    viewCenter.y = std::clamp(viewCenter.y, minY, maxY);

    //set view center
    m_view.setCenter(viewCenter);

	// setting viewport of the view to be:
	// height maximum possible (window.y - HUD.y)
	// width based on height so that proportion stays the same

	float hudPercentage = Modules::Game->getHUDHeight() / window.getSize().y;
    float factor = (((window.getSize().y - Modules::Game->getHUDHeight()) * numberOfTilesWidth / numberOfTilesHeight) / window.getSize().x);
	
    m_view.setViewport(sf::FloatRect((1.0f - factor) / 2, hudPercentage, factor, 1.f - hudPercentage));
    
}

TileInfo Level::getTileInfos(int32_t x, int32_t y) const
{
	if (y >= 0 && y < m_fields.size() && x >= 0 && x < m_fields[0].size())
	{
		//get tile id based on x and y 
		auto tileId = m_fields[y][x].tile->getId();

		//get loaded tileSet infos
		auto tilesetInfoMap = m_levelData.getTilesetInfo();
		auto tileInfoIt = tilesetInfoMap.find(tileId);

		//return the tile info
		if (tileInfoIt != tilesetInfoMap.end())
		{
			//LOG("Tile is : " + tileInfoIt->second);
			return tileInfoIt->second;
		}
	}

	return TileInfo();
}


std::vector<sf::Vector2f> Level::getWalkablePositions() const
{
	std::vector<sf::Vector2f> walkablePositions;

	for (std::size_t y = 0; y < m_fields.size(); ++y)
	{
		for (std::size_t x = 0; x < m_fields[y].size(); ++x)
		{
            if (getTileInfos(static_cast<int32_t>(x), static_cast<int32_t>(y)) == "Walkable")
			{
				walkablePositions.push_back(m_fields[y][x].tilePosition);
			}
		}
	}

	return walkablePositions;
}

std::vector<sf::Vector2f> Level::getUnbreakableObstaclePositions() const
{
    std::vector<sf::Vector2f> unbreakablePositions;

    for (int32_t y = 0; y < m_fields.size(); ++y)
    {
        for (int32_t x = 0; x < m_fields[y].size(); ++x)
        {
            if (getTileInfos(x, y) == "Undestroyable")
            {
                unbreakablePositions.push_back(m_fields[y][x].tilePosition);
            }
        }
    }

    return unbreakablePositions;
}

const std::vector<std::shared_ptr<EnemyBase>>&  Level::getEnemies() const
{
    return m_generatedElements.enemies;
}

const std::vector<std::shared_ptr<Booster>>& Level::getBoosters() const
{
    return m_generatedElements.boosters;
}

const std::vector<std::shared_ptr<Obstacle>>& Level::getObstacles() const
{
    return m_generatedElements.obstacles;
}

const std::shared_ptr<std::vector<std::vector<bool>>> Level::getNavGrid() const
{
    return m_generatedElements.navGrid;
}
