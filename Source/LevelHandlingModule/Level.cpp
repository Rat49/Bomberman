#include "Level.hpp"
#include "Tile.hpp"
#include "LevelData.hpp"
#include "SFML/Graphics.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <Common/Logs.hpp>

namespace
{
	const int32_t NUMBERS_OF_TILE_PER_ROW = 31;
}

Level::Level(const std::string levelConfigPath)
	:m_configPath(levelConfigPath)
{}

bool Level::initialize()
{
	tm.initialize();
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
	std::ifstream file(levelPath);
	if (!file)
	{ 
		LOG("Failed to load level config file from : " + levelPath);
		return false;
	}

	//read each line of file
	int32_t row = 0;
	std::string line;
	while (std::getline(file, line))
	{
		std::vector<FieldInfo> tileRow;
		std::stringstream sStream(line);
		std::string value;
		int32_t col = 0;

		//read row value
		while (std::getline(sStream, value, ','))
		{
			int32_t tempId = std::stoi(value);
			
			FieldInfo newFieldInfo;
			newFieldInfo.tile = tm.getTile(tempId);
			newFieldInfo.tilePosition = { (float)(col * m_levelData.getTileWidth()), (float)(row * m_levelData.getTileHeight()) };
			tileRow.push_back(newFieldInfo);
			++col;
		}

		m_fields.push_back(tileRow);
		++row;
	}

	file.close();

	return true;
}


void Level::setViewOffset(const sf::Vector2f& offset, const sf::RenderWindow& window)
{
	//set it to the window size
	if (m_view.getSize().x == 0 || m_view.getSize().y == 0)
	{
		m_view.setSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
	}

	//calculate the total level width and height in pixels
	float levelPixelWidth = static_cast<float>(m_fields[0].size() * m_levelData.getTileWidth());
	float levelPixelHeight = static_cast<float>(m_fields.size() * m_levelData.getTileHeight());

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
	for (std::size_t row = 0; row < m_fields.size(); ++row) {
		for (std::size_t col = 0; col < m_fields[row].size(); ++col) {
			const FieldInfo& fieldInfo = m_fields[row][col];

			Tile drawableTile = *fieldInfo.tile;
			drawableTile.setPosition(fieldInfo.tilePosition);

			target.draw(drawableTile, states);
		}
	}
}

sf::Vector2f Level::getTilePosition(int32_t row, int32_t col) const
{
	if (col >= 0 && col < m_fields.size() && row >= 0 && row < m_fields[0].size())
	{
		LOG("Tile [$][$]:{$, $}({row, col})", row, col, m_fields[row][col].tilePosition.x, m_fields[row][col].tilePosition.y);
		return m_fields[row][col].tilePosition;
	}
	return { -1.f, -1.f };
}

TileID Level::getTileID(int32_t row, int32_t col) const
{
	if (col >= 0 && col < m_fields.size() && row >= 0 && row < m_fields[0].size())
	{
		return m_fields[col][row].tile->getId();
	}
	return -1;
}

sf::Vector2i Level::getTileRowCol(float x, float y) const
{
	int32_t col = static_cast<int>(x / 32.f);
	int32_t row = static_cast<int>(y / 32.f);
	LOG("ROWCOOL $ | $", row, col);
	if (row < 0 || row >= m_fields[0].size() || col < 0 || col >= m_fields.size())
	{
		return { 0,0 };
	}
	return { row, col };
}

bool Level::setNewTile(int32_t row, int32_t col, TileID tileID)
{
	if (col >= 0 && col < m_fields.size() && row >= 0 && row < m_fields[0].size())
	{
		m_fields[row][col].tile = tm.getTile(tileID);
		return true;
	}
	return false;
}

std::shared_ptr<std::vector<std::vector<FieldInfo>>> Level::getLevelFields() const
{
	return std::make_shared<std::vector<std::vector<FieldInfo>>>(m_fields);
}

TileInfo Level::getTileInfos(int32_t x, int32_t y) const
{
	if (y >= 0 && y < m_fields.size() && x >= 0 && x < m_fields[0].size())
	{
		//get tile id based on x and y 
		auto tileId = m_fields[y][x].tile->getId();

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