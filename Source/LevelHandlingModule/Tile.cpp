#include "Tile.hpp"
#include "SFML/Graphics.hpp"
#include <Common/Logs.hpp>

Tile::Tile() 
{
	m_id        = -1;
}

bool Tile::initialize(int32_t tileId, const sf::IntRect& textureRect, const std::shared_ptr<sf::Texture>& atlasTexture)
{
	if (!atlasTexture)
	{
		LOG("Failed to load texture");
		return false;
	}
	
	m_id      = tileId;
	setTexture(*atlasTexture);
	setTextureRect(textureRect);

	return true;
}

