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

    std::unordered_map<std::int32_t, std::string> getTilesetInfo() const
    {
        return m_tilesetInfo;
    }

    std::string getLevelElementsConfigPath() const
    {
        return m_levelElementsConfigPath;
    }

    std::string getTilesetAssetConfigPath() const
    {
        return m_tilesAssetsConfig;
    }

    std::string getTilesetPath() const
    {
        return m_tilesetPath;
    }

    std::string getAtlasPath() const
    {
        return m_atlasPath;
    }

    std::string getLevelPath() const
    {
        return m_levelPath;
    }

    int32_t getTileHeight() const
    {
        return m_tileHeight;
    }

    int32_t getTileWidth() const
    {
        return m_tileWidth;
    }

private:
    std::unordered_map<std::int32_t, std::string> m_tilesetInfo;

    std::string m_levelElementsConfigPath;

    std::string m_tilesAssetsConfig;

    std::string m_tilesetPath;

    std::string m_atlasPath;

    std::string m_levelPath;

    int32_t m_tileHeight;

    int32_t m_tileWidth;
};
