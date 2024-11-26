#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Tile : public sf::Sprite
{
public:
	Tile();
	
	bool initialize(int32_t tileId, const sf::IntRect& textureRect, const std::shared_ptr<sf::Texture>& atlasTexture);

	int32_t getId() const { return m_id; }

private:
	int32_t m_id;

};