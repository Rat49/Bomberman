#pragma once

#include <string>
#include "SFML/Graphics.hpp"
#include "Level.hpp"
#include "BaseModule/BaseModule.hpp"


class LevelHandlingModule : public BaseModule
{
private:

	std::unique_ptr<Level> m_level;

public:

	// create level using config file
	void createLevel(const std::string& configPath);

	//draw level on screen
	void draw(sf::RenderWindow& window) const;

	//check if level is loaded 
	bool isLevelLoaded() const;
	void terminate() override;
};

