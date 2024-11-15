#include "Level.hpp"
#include "Tile.hpp"
#include "LevelData.hpp"
#include "SFML/Graphics.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <Common/Logs.hpp>


Level::Level(const std::string levelConfigPath)
	:m_configPath(levelConfigPath)
{}

bool Level::initialize()
{
	//load level configuration data
	if (!m_levelData.loadLevelConfigData(m_configPath))
	{
		LOG("Failed to load level data from: " + m_configPath);
		return false;
	}

	//load tileSet configuration data (tileTypes)
	if (!m_levelData.loadTilesetConfigData(m_levelData.getTilesetPath()))
	{
		LOG("Failed to load tileSet data from : " + m_levelData.getTilesetPath());
		return false;
	}

	//load the atlas texture using the path from level data
	if (!loadTexture(m_levelData.getAtlasPath()))
	{
		LOG("Failed to load texture from : " + m_levelData.getAtlasPath());
		return false;
	}

	//initialize level tiles based on tile IDs
	if (!loadLevel(m_levelData.getLevelPath()))
	{
		LOG("Failed to load level from : " + m_levelData.getLevelPath());
		return false;
	}

	return true;
}

bool Level::loadLevel(const std::string& levelPath)
{
	//open level file for reading
	std::ifstream file(levelPath);
	if (!file)
	{ 
		LOG("Failed to load level config file from : " + levelPath);
		return false;
	}

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
			//set value to int
			int32_t tempId = std::stoi(value);

			//calculate rect of tile
			int32_t numTilesPerRow = m_atlasTexture->getSize().x / m_levelData.getTileWidth();
			int32_t tileIndexX = (tempId % numTilesPerRow) * m_levelData.getTileWidth();
			int32_t tileIndexY = (tempId / numTilesPerRow) * m_levelData.getTileHeight();
			sf::IntRect textureRect(tileIndexX, tileIndexY, m_levelData.getTileWidth(), m_levelData.getTileHeight());

			//calculate position of tile
			sf::Vector2f position(static_cast<float>(columnIndex * m_levelData.getTileWidth()), static_cast<float>(rowIndex * m_levelData.getTileHeight()));

			Tile tile;
			if (!tile.initialize(tempId, textureRect, position, m_atlasTexture))
			{ 
				LOG("Failed to initialize tile with index : " + rowIndex, columnIndex);
				return false;
			}
			
			//add tile
			tileRow.push_back(tile);
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
	//set it to the window size
	if (m_view.getSize().x == 0 || m_view.getSize().y == 0)
	{
		m_view.setSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
	}

	//calculate the total level width and height in pixels
	float levelPixelWidth = static_cast<float>(m_tiles[0].size() * m_levelData.getTileWidth());
	float levelPixelHeight = static_cast<float>(m_tiles.size() * m_levelData.getTileHeight());

	//initialize view center to the target offset position
	sf::Vector2f viewCenter = offset;

	//define minimum and maximum bounds
	float minX = m_view.getSize().x / 2.f;
	float maxX = std::max(levelPixelWidth - m_view.getSize().x / 2.f, minX);
	float minY = m_view.getSize().y / 2.f;
	float maxY = std::max(levelPixelHeight - m_view.getSize().y / 2.f, minY);

	//clamp the view center coordinates to ensure they remain within level bounds
	viewCenter.x = std::clamp(viewCenter.x, minX, maxX);
	viewCenter.y = std::clamp(viewCenter.y, minY, maxY);

	//set view center
	m_view.setCenter(viewCenter); 

	//adjust the view size
	if (levelPixelWidth > window.getSize().x || levelPixelHeight > window.getSize().y)
	{
		//level is larger than the window
		m_view.setSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
	}
	else
	{
		//level is smaller than the window
		m_view.setSize(levelPixelWidth, levelPixelHeight); 
	}
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

TileInfo Level::getTileInfos(int32_t x, int32_t y) const
{
	if (y >= 0 && y < m_tiles.size() && x >= 0 && x < m_tiles[0].size())
	{
		//get tile id based on x and y 
		auto tileId = m_tiles[y][x].getId();

		//get loaded tileSet infos
		auto tilesetInfoMap = m_levelData.getTilesetInfo();
		auto tileInfoIt = tilesetInfoMap.find(tileId);

		//return the tile info
		if (tileInfoIt != tilesetInfoMap.end())
		{
			LOG("Tile is : " + tileInfoIt->second);
			return tileInfoIt->second;
		}
	}

	return TileInfo();
}
