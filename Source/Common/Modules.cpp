#include "Common/Modules.hpp"
#include "GameModule/GameModule.hpp"
#include "TestModule/TestModule.hpp"
#include "LogModule/LogManager.hpp"


std::unique_ptr<GameModule> Modules::Game;
std::unique_ptr<TestModule> Modules::Tests;
std::unique_ptr<LogManager> Modules::Logs;

void Modules::initialize()
{
	Modules::Game = std::make_unique<GameModule>();
	Modules::Tests = std::make_unique<TestModule>();
	Modules::Logs = std::make_unique<LogManager>();
}

void Modules::terminate()
{
	Modules::Tests.release();
	Modules::Game.release();
	Modules::Logs.release();
}
