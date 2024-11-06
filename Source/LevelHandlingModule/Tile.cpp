#include "Tile.hpp"
#include "SFML/Graphics/Texture.hpp"

Tile::Tile(const int32_t tileId, const int32_t tileWidth, const int32_t tileHeight, const std::shared_ptr<sf::Texture>& atlasTexture, const int32_t columnIndex, const int32_t rowIndex)
	:m_id(tileId),m_width(tileWidth),m_height(tileHeight)
{
	if (!atlasTexture)
		return;

	//calculate position
	int32_t numTilesPerRow = atlasTexture->getSize().x / tileWidth;
	int32_t tileIndexX = (tileId % numTilesPerRow) * tileWidth;
	int32_t tileIndexY = (tileId / numTilesPerRow) * tileHeight;

	//set atlas and rect of atlas to tile
	setTexture(*atlasTexture);
	setTextureRect(sf::IntRect(tileIndexX, tileIndexY, tileWidth, tileHeight));

	//set position
	setPosition(static_cast<float>(columnIndex * tileWidth), static_cast<float>(rowIndex * tileHeight));
}
