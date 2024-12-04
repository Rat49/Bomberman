#include "Level.hpp"
#include "Tile.hpp"
#include "LevelData.hpp"
#include "SFML/Graphics.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <Common/Logs.hpp>
#include "Common/Modules.hpp"
#include "AssetManager/AssetManager.hpp"
#include "ConfigSystem/ConfigSystem.hpp"

namespace
{
	const std::string ID = "id";
	const std::string X_COORD = "x";
	const std::string Y_COORD = "y";
	const std::string ATLAS_PATH = "Game/Textures/levelAtlas.png";
	const int8_t ATLAS_SPRITE_SIZE = 64;
}

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

	//initialize level tiles based on tile IDs
	if (!loadTiles())
	{
		LOG("Failed to load tiles for the level");
		return false;
	}

	//initialize level tiles based on tile IDs
	if (!loadLevel(m_levelData.getLevelPath()))
	{
		LOG("Failed to load level from : " + m_levelData.getLevelPath());
		return false;
	}

	// Setting Viewport so that HUD is always shown at the top of the window
	m_view.setViewport(sf::FloatRect(0.0f, 0.1f, 1.f, 0.9f));

	return true;
}

bool Level::loadTiles() 
{
	m_atlasTexture = Modules::Assets->getTexture(ATLAS_PATH);

	Modules::Config->addFile(m_levelData.getTilesetAssetConfigPath());
	const ConfigFile& tileTexturesSettings = Modules::Config->getFile(m_levelData.getTilesetAssetConfigPath());
	const auto& sections = tileTexturesSettings.getAllSections();

	for (const auto& section : sections)
	{
		int32_t id = tileTexturesSettings.getSection(section).getValue(ID).getInt32();
		int32_t x = tileTexturesSettings.getSection(section).getValue(X_COORD).getInt32();
		int32_t y = tileTexturesSettings.getSection(section).getValue(Y_COORD).getInt32();

		Tile newTile;
		sf::IntRect newRect(x, y, ATLAS_SPRITE_SIZE, ATLAS_SPRITE_SIZE);
		newTile.initialize(id, newRect, m_atlasTexture);
		m_availableTiles.emplace(id, std::make_shared<Tile>(newTile));
		if (!m_availableTiles[id])
		{
			return false;
		}
	}

	return true;
}

bool Level::loadLevel(const std::string& levelPath)
{
	//use Asset Manager to get level file data
	const auto levelData = Modules::Assets->getLevel(levelPath);

	if (levelData->empty())
	{
		LOG("Failed to load level .csv file from [$]", levelPath);
		return false;
	}

	//convert data in string stream
	std::string levelString(levelData->begin(), levelData->end());
	std::istringstream file(levelString);

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
			newFieldInfo.tile = m_availableTiles[tempId];
			newFieldInfo.tilePosition = { (float)(col * m_levelData.getTileWidth()), (float)(row * m_levelData.getTileHeight()) };
			tileRow.push_back(newFieldInfo);
			++col;
		}

		m_fields.push_back(tileRow);
		++row;
	}

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
			//LOG("Tile is : " + tileInfoIt->second);
			return tileInfoIt->second;
		}
	}

	return TileInfo();
}

std::vector<sf::Vector2f> Level::getWalkablePositions() const
{
	std::vector<sf::Vector2f> walkablePositions;

	for (std::size_t y = 0; y < m_fields.size(); ++y)
	{
		for (std::size_t x = 0; x < m_fields[y].size(); ++x)
		{
			if (getTileInfos(static_cast<int32_t>(x), static_cast<int32_t>(y)) == "Walkable")
			{
				walkablePositions.push_back(m_fields[y][x].tilePosition);
			}
		}
	}

	return walkablePositions;
}
