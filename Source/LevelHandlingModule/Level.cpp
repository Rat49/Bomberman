#include "Level.hpp"
#include "Tile.hpp"
#include "LevelData.hpp"
#include "SFML/Graphics.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>


Level::Level(const std::string levelConfigPath)
{
	//load level configuration data
	if (!m_levelData.loadLevelData(levelConfigPath))
		return;

	//load the atlas texture using the path from level data
	if (!loadTexture(m_levelData.getAtlasPath()))
		return;

	//initialize level tiles based on tile IDs
	if (!loadLevel(m_levelData.getLevelPath()))
		return;
}

bool Level::loadLevel(const std::string& levelPath)
{
	//open level file for reading
	std::ifstream file(levelPath);
	if (!file)
		return false;

	//read each line of file
	int32_t rowIndex = 0;
	std::string line;
	while (std::getline(file, line))
	{
		std::vector<Tile> tileRow;
		std::stringstream sStream(line);
		std::string value;
		int32_t columnIndex = 0;

		//read row value
		while (std::getline(sStream, value, ','))
		{
			int32_t tempId = std::stoi(value);

			//add a new Tile object to the current row
			tileRow.emplace_back(tempId, m_levelData.getTileWidth(), m_levelData.getTileHeight(), m_atlasTexture, columnIndex, rowIndex);
			++columnIndex;
		}

		//add the completed row of tiles
		m_tiles.push_back(tileRow);
		++rowIndex;
	}

	file.close();

	return true;
}

bool Level::loadTexture(const std::string& texturePath)
{
	m_atlasTexture = std::make_shared<sf::Texture>();
	return m_atlasTexture->loadFromFile(texturePath);
}

void Level::setViewOffset(const sf::Vector2f& offset, const sf::RenderWindow& window)
{

	if (m_view.getSize().x == 0 || m_view.getSize().y == 0)
	{
	
		m_view.setSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
	}

	float levelPixelWidth = static_cast<float>(m_tiles[0].size() * m_levelData.getTileWidth());
	float levelPixelHeight = static_cast<float>(m_tiles.size() * m_levelData.getTileHeight());


	sf::Vector2f viewCenter = offset;


	float minX = m_view.getSize().x / 2.f;
	float maxX = std::max(levelPixelWidth - m_view.getSize().x / 2.f, minX);
	float minY = m_view.getSize().y / 2.f;
	float maxY = std::max(levelPixelHeight - m_view.getSize().y / 2.f, minY);

	viewCenter.x = std::clamp(viewCenter.x, minX, maxX);
	viewCenter.y = std::clamp(viewCenter.y, minY, maxY);

	m_view.setCenter(viewCenter); 


	if (levelPixelWidth > window.getSize().x || levelPixelHeight > window.getSize().y)
	{
		m_view.setSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
	}
	else
	{
		m_view.setSize(levelPixelWidth, levelPixelHeight); 
	}

	
}
const sf::View& Level::getView() const {
	return m_view;
}



void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.setView(m_view);

	for (const auto& row : m_tiles)
	{
		for (const auto& tile : row)
		{
			//draw Tile sprites with positions
			target.draw(tile, states);
		}
	}
}

TileType Level::getTileType(int32_t x, int32_t y)
{
	if (y < m_tiles.size() && x < m_tiles[0].size())
	{
		return m_tiles[y][x].getType();
	}

	//default
	return TileType::Unknown;
}

void Level::destroyTile(int32_t x, int32_t y)
{
	if (y < m_tiles.size() && x < m_tiles[0].size())
	{
		Tile& tile = m_tiles[y][x];
		if (tile.getType() == TileType::Destroyable_Wall)
		{
			//set ground tile on that position
			tile = Tile(22, m_levelData.getTileWidth(), m_levelData.getTileHeight(), m_atlasTexture, x, y);
		}
	}
}

bool Level::isTileWalkable(int32_t x, int32_t y)
{
	if (y < m_tiles.size() && x < m_tiles[0].size())
	{
		return  m_tiles[y][x].getType() == TileType::Ground;
	}
	return false;
}





