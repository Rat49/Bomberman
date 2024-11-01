#pragma once
#include "BaseModule/BaseModule.hpp"

/*
* This is a general manger class. Holder of all modules. You can access it from any part of the game
*/
class GameModule : public BaseModule
{
public:
	void run();

	void terminate() override;
};
