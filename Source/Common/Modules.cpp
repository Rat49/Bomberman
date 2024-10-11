#include "Common/Modules.hpp"
#include "GameModule/GameModule.hpp"
#include "TestModule/TestModule.hpp"
#include "LogModule/LogManager.hpp"
#include "EventSystem/EventSystem.hpp"
#include "ConfigSystem/ConfigSystem.hpp"

#ifndef FINAL
std::unique_ptr<TestModule> Modules::Tests;
std::unique_ptr<LogManager> Modules::Logs;
#endif

std::unique_ptr<GameModule> Modules::Game;
std::unique_ptr<EventSystem> Modules::Events;
std::unique_ptr<ConfigSystem> Modules::Config;

void Modules::initialize()
{
#ifndef FINAL
	Modules::Logs = std::make_unique<LogManager>();
	Modules::Tests = std::make_unique<TestModule>();
#endif

	Modules::Game = std::make_unique<GameModule>();
	// add your modules here
	Modules::Events = std::make_unique<EventSystem>();
	Modules::Config = std::make_unique<ConfigSystem>();
}

void Modules::terminate()
{
	Modules::Game.release();
	// add your modules here
	Modules::Events.release();
	Modules::Config.release();

#ifndef FINAL
	Modules::Tests.release();
	Modules::Logs.release();
#endif
}
