#include "Common/Modules.hpp"
#include "GameModule/GameModule.hpp"
#include "TestModule/TestModule.hpp"

#ifndef FINAL
std::unique_ptr<TestModule> Modules::Tests;
#endif

std::unique_ptr<GameModule> Modules::Game;

void Modules::initialize()
{
#ifndef FINAL
	Modules::Tests = std::make_unique<TestModule>();
#endif

	Modules::Game = std::make_unique<GameModule>();
	// add your modules here
}

void Modules::terminate()
{
	Modules::Game.release();
	// add your modules here

#ifndef FINAL
	Modules::Tests.release();
#endif
}
