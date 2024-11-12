#pragma once

#include "SFML/Graphics/Sprite.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <memory>


enum TileType
{
	Ground,
	Destroyable_Wall,
	Wall,
	Unknown
};


class Tile : public sf::Sprite
{
private:

	TileType m_type;
	int32_t m_id;;
	sf::Vector2f m_position;

public:

	Tile(const int32_t tileId, const int32_t tileWidth, const int32_t tileHeight, const std::shared_ptr<sf::Texture>& atlasTexture, const int32_t columnIndex, const int32_t rowIndex);

	void setType(const int32_t tileId);
	const TileType getType() const { return m_type; }
	
	const int32_t getId() const { return m_id; }
	const sf::Vector2f getPosition() const { return m_position; }


};

