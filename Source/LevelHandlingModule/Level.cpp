#include "Level.hpp"
#include "Tile.hpp"
#include "LevelData.hpp"
#include "SFML/Graphics.hpp"
#include <fstream>
#include <sstream>
#include <string>


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

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& row : m_tiles) 
	{
		for (const auto& tile : row) 
		{
			//draw Tile sprites with positions
			target.draw(tile, states);
		}
	}

}
