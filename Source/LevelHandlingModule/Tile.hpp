#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "TileTypes.hpp"

class Tile : public sf::Sprite
{
public:
	Tile();
	
	bool initialize(TileID tileId, const sf::IntRect& textureRect, const std::shared_ptr<sf::Texture>& atlasTexture);

	TileID getId() const { return m_id; }

private:
	TileID m_id;

};