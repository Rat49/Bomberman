#include "Tile.hpp"
#include "SFML/Graphics/Texture.hpp"

Tile::Tile(const int32_t tileId, const int32_t tileWidth, const int32_t tileHeight, const std::shared_ptr<sf::Texture>& atlasTexture, const int32_t columnIndex, const int32_t rowIndex)
	:m_id(tileId)
{
	//set texture (atlas)
	if (!atlasTexture)
		return;

	setTexture(*atlasTexture);


	//calculate position of tile in atlas and set rect
	int32_t numTilesPerRow = atlasTexture->getSize().x / tileWidth;
	int32_t tileIndexX = (m_id % numTilesPerRow) * tileWidth;
	int32_t tileIndexY = (m_id / numTilesPerRow) * tileHeight;

	setTextureRect(sf::IntRect(tileIndexX, tileIndexY, tileWidth, tileHeight));


	//set position on level
	m_position.x = static_cast<float>(columnIndex * tileWidth);
	m_position.y = static_cast<float>(rowIndex* tileHeight);
	setPosition(m_position);

	//set type
	setType(tileId);

}

void Tile::setType(const int32_t tileId)
{
	switch (tileId)
	{
	case 22 :
		m_type = TileType::Ground;
		break;

	case 899 :
		m_type = TileType::Wall;
		break;

	case 902 :
		m_type = TileType::Destroyable_Wall;
		break;

	default:

		m_type = TileType::Unknown;
		break;
	}
}
