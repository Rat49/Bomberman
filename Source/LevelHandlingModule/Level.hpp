#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include "LevelData.hpp"
#include "Tile.hpp"
#include <vector>

class Level : public sf::Drawable
{
private:

	std::vector<std::vector<Tile>> m_tiles;
	LevelData m_levelData;
	std::shared_ptr<sf::Texture> m_atlasTexture;

public:
	
	//constructor for the Level class that loads level data, the atlas texture, and initializes all tiles.
	Level(const std::string levelConfigPath);

	//draws all the tiles in the level to the specified render target
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	//get tile from 
	TileType getTileType(int32_t x, int32_t y);

	//destroy tile
	void destroyTile(int32_t x, int32_t y);

	//check if tile is walkable
	bool isTileWalkable(int32_t x, int32_t  y);

private:

	//loads the level configuration from a file and creates tiles with IDs.
	bool loadLevel(const std::string& levelPath);

	//loads the atlas texture containing the tile sprites.
	bool loadTexture(const std::string& texturePath);
};



