#pragma once
#include "BaseModule/BaseModule.hpp"
#include "HUD.hpp"

/*
* This is a general manger class. Holder of all modules. You can access it from any part of the game
*/
class GameModule : public BaseModule
{
public:
	bool initialize() override;

	void run();

	void terminate() override;

private:
	sf::RenderWindow window;
	std::unique_ptr<HUD> hud;
};
