#pragma once
#include <memory>

class GameModule;
class TestModule;
class EventSystem;

/*
* This is a general manger class. Holder of all modules. You can access it from any part of the game
*/
struct Modules
{
	static void initialize();
	static void terminate();

	static std::unique_ptr<GameModule> Game;
	static std::unique_ptr<TestModule> Tests;
	static std::unique_ptr<EventSystem> EventSystems;
};