#pragma once

#include <string>
#include "SFML/Graphics.hpp"
#include "Level.hpp"
#include "BaseModule/BaseModule.hpp"

using LevelId = int32_t;

class LevelHandlingModule : public BaseModule
{
public:

	//load level using config file
	LevelId loadLevel(const std::string& configPath);

	//load multiple levels using config file vector 
	std::vector<LevelId> loadLevels(const std::vector<std::string>& configPaths);

	//set level 
	void setCurrentLevel(LevelId levelId);

	//check if level is loaded 
	bool isLevelLoaded(LevelId levelId) const;

	//set offset based on player position
	void setLevelViewOffset(const sf::Vector2f& offset, const sf::RenderWindow& window);

	//draw level on window
	void update(float, sf::Window* window) override;

	//remove levels from data member
	void terminate() override;

private:

	//vector to store loaded levels
	std::vector<std::shared_ptr<Level>> m_levels;

	//id of current level
	LevelId m_currentLevel;


};

