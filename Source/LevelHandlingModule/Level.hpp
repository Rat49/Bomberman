#pragma once

#include "SFML/Graphics.hpp"
#include "LevelData.hpp"
#include "Tile.hpp"
#include <vector>

class Level : public sf::Drawable
{
public:

	//constructor for the Level class that loads level data, the atlas texture, and initializes all tiles.
	Level(const std::string levelConfigPath);

	//level view config
	void setViewOffset(const sf::Vector2f& offset, const sf::RenderWindow& window);

	//draws all the tiles in the level to the specified render target
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	//loads the level configuration from a file and creates tiles with IDs.
	bool loadLevel(const std::string& levelPath);

	//loads the atlas texture containing the tile sprites.
	bool loadTexture(const std::string& texturePath);


private:

	sf::View m_view;

	std::vector<std::vector<Tile>> m_tiles;

	LevelData m_levelData;

	std::shared_ptr<sf::Texture> m_atlasTexture;

};



