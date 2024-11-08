#pragma once

#include <string>
#include "SFML/Graphics.hpp"
#include "Level.hpp"
#include "BaseModule/BaseModule.hpp"

using LevelId = int32_t;

class LevelHandlingModule : public BaseModule
{
private:

	//vector to store loaded levels
	std::vector<std::shared_ptr<Level>> m_levels;
	LevelId m_currentLevel;

public:

	//load level using config file
	LevelId loadLevel(const std::string& configPath);

	//load multiple levels using config file vector 
	std::vector<LevelId> loadLevels(const std::vector<std::string>& configPaths);

	//get loaded level using id 
	std::shared_ptr<Level> getLevel(LevelId levelId) const;

	//draw level on screen
	void drawLevel(sf::RenderWindow& window, LevelId levelId) const;

	//check if level is loaded 
	bool isLevelLoaded(LevelId levelId) const;

	//destroy tile if it's destroyable wall
	void destroyTileFromLevel(LevelId levelId, int32_t x, int32_t y); 

	//check if tile isWalkable
	bool isWalkable(LevelId levelId, int32_t x, int32_t y);

	//get type of tile using level id and tile coordinates 
	TileType getTileType(LevelId levelId, int32_t x, int32_t y);

	//remove levels from data member
	void terminate() override;
};

