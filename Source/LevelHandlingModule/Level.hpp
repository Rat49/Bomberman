#pragma once

#include "SFML/Graphics.hpp"
#include "LevelData.hpp"
#include "Tile.hpp"
#include "TileManager.hpp"
#include <vector>

using TileInfo = std::string;

struct FieldInfo {
	std::shared_ptr<Tile> tile;
	sf::Vector2f tilePosition;
};

class Level : public sf::Drawable
{
public:
	Level(const std::string configFilePath);

	bool initialize();

	//level view config
	void setViewOffset(const sf::Vector2f& offset, const sf::RenderWindow& window);

	//draws all the tiles in the level to the specified render target
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	TileInfo Level::getTileInfos(int32_t x, int32_t y) const;

	sf::Vector2f getTilePosition(int32_t row, int32_t col) const;

	TileID getTileID(int32_t row, int32_t col) const;

	sf::Vector2i Level::getTileRowCol(float x, float y) const;

	bool setNewTile(int32_t row, int32_t col, TileID tileID);

	std::shared_ptr<std::vector<std::vector<FieldInfo>>> getLevelFields() const;

private:

	//loads the level configuration from a file and creates tiles with IDs.
	bool loadLevel(const std::string& levelPath);

private:

	std::string m_configPath;

	sf::View m_view;

	std::vector<std::vector<FieldInfo>> m_fields;

	LevelData m_levelData;

	TileManager tm;
};



