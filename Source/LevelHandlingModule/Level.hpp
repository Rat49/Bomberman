#pragma once

#include "SFML/Graphics.hpp"
#include "LevelShared.hpp"
#include "LevelData.hpp"
#include "Tile.hpp"
#include <vector>

using TileInfo = std::string;

class ElementsGenerator;
class Obstacle;
class Enemy;
class Booster;
class Gate;
class Key;

struct FieldInfo
{
	std::shared_ptr<Tile> tile;
	sf::Vector2f tilePosition;
};

class Level : public sf::Drawable
{
public:

	Level(const std::string baseLevelConfigPath);

	//initialize level
	bool initialize();

	//set elements on level
	bool setUpElements(int32_t levelElementsId);

	//level view config
	void setViewOffset(const sf::Vector2f& offset, const sf::RenderWindow& window);

	//draws all the tiles in the level to the specified render target
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	//get information of tile based on position and return TileInfo
	TileInfo Level::getTileInfos(int32_t x, int32_t y) const;

	//return all walkable positions on level 
	std::vector<sf::Vector2f> getWalkablePositions() const;

	std::vector<std::shared_ptr<Enemy>>& getEnemies() const;

	std::vector<std::shared_ptr<Booster>>& getBoosters() const;

	std::vector<std::shared_ptr<Obstacle>>& getObstacles() const;

private:

	//loads the level configuration from a file and creates tiles with IDs.
	bool loadLevel(const std::string& levelPath);

	//load level config data for generating elements on level
	bool loadConfig(const std::string levelConfigPath);

	//load, initialize and store tiles
	bool loadTiles();

	//add generated elements on level

	void addObstacles(const std::vector<std::shared_ptr<Obstacle>>& obstacles);

	void addEnemies(const std::vector<std::shared_ptr<Enemy>>& enemies);

	void addGates(const std::vector<std::shared_ptr<Gate>>& gates);

	void addKeys(const std::vector<std::shared_ptr<Key>>& keys);

	void addBoosters(const std::vector<std::shared_ptr<Booster>>& boosters);

private:

	sf::View m_view;

	LevelData m_levelData;

	LevelConfigs m_levelConfig;

	GeneratedElements m_generatedElements;
	
	std::unordered_map<int32_t, LevelConfigs> m_levelConfigData;

	std::map<int32_t, std::shared_ptr<Tile>> m_availableTiles;

	std::unique_ptr<ElementsGenerator> m_elementsGenerator;

	std::shared_ptr<sf::Texture> m_atlasTexture;

	std::vector<std::vector<FieldInfo>> m_fields;

	std::string m_configPath;

};



