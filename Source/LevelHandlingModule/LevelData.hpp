#pragma once

#include <string>
#include <unordered_map>

class LevelData
{
public:

	//loads level configuration data from path
	bool loadLevelConfigData(const std::string& configLevelPath);

	//load tileSet configuration (tileTypes based on ids)
	bool loadTilesetConfigData(const std::string& configTilesetPath);
	
	//getters to access level data attributes

	std::string getAtlasPath() const { return m_atlasPath; }

	std::string getLevelPath() const { return m_levelPath; }
	
	std::string getTilesetPath() const { return m_tilesetPath; }

	std::string getTilesetAssetConfigPath() const { return m_tilesAssetsConfig; }

	int32_t getTileWidth() const { return m_tileWidth; }

	int32_t getTileHeight() const { return m_tileHeight; }

	std::unordered_map<std::int32_t, std::string> getTilesetInfo() const { return m_tilesetInfo; }

private:

	std::string m_atlasPath;
	
	std::string m_levelPath;
	
	std::string m_tilesetPath;

	std::string m_tilesAssetsConfig;
	
	int32_t m_tileWidth;
	
	int32_t m_tileHeight;

	std::unordered_map<std::int32_t, std::string> m_tilesetInfo;

};

