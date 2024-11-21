#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "BaseModule/BaseModule.hpp"
#include "Tile.hpp"

class TileManager
{
public:
	TileManager();

	void initialize();

	std::shared_ptr<Tile> getTile(TileID tileID);

private:
	std::map<TileID, std::shared_ptr<Tile>> m_availableTiles;

	std::shared_ptr<sf::Texture>  m_atlasTexture;

};

