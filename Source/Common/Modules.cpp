#include "Common/Modules.hpp"
#include "GameModule/GameModule.hpp"
#include "TestModule/TestModule.hpp"


std::unique_ptr<GameModule> Modules::Game;
std::unique_ptr<TestModule> Modules::Tests;

void Modules::initialize()
{
	Modules::Game = std::make_unique<GameModule>();
	Modules::Tests = std::make_unique<TestModule>();
}

void Modules::terminate()
{
	Modules::Tests.release();
	Modules::Game.release();
}
