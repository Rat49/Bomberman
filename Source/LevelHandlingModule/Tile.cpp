#include "Tile.hpp"
#include "SFML/Graphics.hpp"
#include <Common/Logs.hpp>

Tile::Tile()
	:m_id(-1), m_position(0.f, 0.f) //default values
{}

bool Tile::initialize(int32_t tileId, const sf::IntRect& textureRect, const sf::Vector2f& position, const std::shared_ptr<sf::Texture>& atlasTexture)
{
	if (!atlasTexture)
	{
		LOG("Failed to load texture");
		return false;
	}
	
	m_id = tileId;
	m_position = position;

	setTexture(*atlasTexture);
	setTextureRect(textureRect);
	setPosition(position);

	return true;
}

