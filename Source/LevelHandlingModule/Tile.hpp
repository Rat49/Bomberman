#pragma once

#include "SFML/Graphics/Sprite.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <memory>


class Tile : public sf::Sprite
{
private:

	int32_t m_id;
	int32_t m_width , m_height;

public:

	Tile(const int32_t tileId, const int32_t tileWidth, const int32_t tileHeight, const std::shared_ptr<sf::Texture>& atlasTexture, const int32_t columnIndex, const int32_t rowIndex);
};

