#pragma once

#include <string>

class LevelData
{
public:

	//loads level configuration data from path
	bool loadLevelData(const std::string& configLevelPath);
	
	//getters to access level data attributes

	std::string getAtlasPath() const { return m_atlasPath; }

	std::string getLevelPath() const { return m_levelPath; }

	int32_t getTileWidth() const { return m_tileWidth; }

	int32_t getTileHeight() const { return m_tileHeight; }

private:

	std::string m_atlasPath;
	
	std::string m_levelPath;
	
	int32_t m_tileWidth;
	
	int32_t m_tileHeight;
};

