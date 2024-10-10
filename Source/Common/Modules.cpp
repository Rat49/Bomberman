#include "Common/Modules.hpp"
#include "GameModule/GameModule.hpp"
#include "TestModule/TestModule.hpp"
#include "EventSystem/EventSystem.hpp"


std::unique_ptr<GameModule> Modules::Game;
std::unique_ptr<TestModule> Modules::Tests;
std::unique_ptr<EventSystem> Modules::EventSystems;


void Modules::initialize()
{
	Modules::Game = std::make_unique<GameModule>();
	Modules::Tests = std::make_unique<TestModule>();
	Modules::EventSystems = std::make_unique<EventSystem>();
}

void Modules::terminate()
{
	Modules::Tests.release();
	Modules::Game.release();
	Modules::EventSystems.release();
}
