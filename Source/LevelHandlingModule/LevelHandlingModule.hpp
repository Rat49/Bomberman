#pragma once

#include "BaseModule/BaseModule.hpp"
#include "Level.hpp"
#include "SFML/Graphics.hpp"
#include "memory"
#include <string>

using LevelId                      = int32_t;
constexpr LevelId INVALID_LEVEL_ID = -1;

class LevelHandlingModule : public BaseModule
{
public:
    //load level using config file
    LevelId loadLevel(const std::string& configPath);

    //load multiple levels using config file vector
    bool loadLevels(const std::vector<std::string>& configPaths);

    //setUp elements on level
    bool setUpElementsOnLevel(int32_t levelElementsId);

    //unload level from map
    bool unloadLevel(LevelId levelId);

    //set level
    void setCurrentLevel(LevelId levelId);

    //get level
    LevelId getCurrentLevelID() const;

    std::shared_ptr<Level> getCurrentLevel() const;

    //check if level is loaded
    bool isLevelLoaded(LevelId levelId) const;

    //set offset based on player position
    void setLevelViewOffset(const sf::Vector2f& offset, const sf::RenderWindow& window);

    //get level tile info based on tile id
    TileInfo getTileInfo(int32_t x, int32_t y);

    std::vector<sf::Vector2f> getWalkablePositions() const;

    std::vector<sf::Vector2f> getUnbreakableObstaclePositions() const;

    //draw level on window
    void update(float, sf::Window*) override;

    //remove levels from data member
    void terminate() override;

    std::shared_ptr<Level> getCurrentLevelPtr()
    {
        return m_levels[m_currentLevelID];
    }

private:
    //store loaded levels
    mutable std::unordered_map<LevelId, std::shared_ptr<Level>> m_levels;

    //id of current level
    LevelId m_currentLevelID = -1;

    //temp Level id
    LevelId m_levelId = -1;
};
