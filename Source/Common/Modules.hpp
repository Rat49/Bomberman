#pragma once
#include <memory>

class GameModule;
class TestModule;

/*
* This is a general manger class. Holder of all modules. You can access it from any part of the game
*/
struct Modules
{
	static void initialize();
	static void terminate();

	static std::unique_ptr<GameModule> Game;
	static std::unique_ptr<TestModule> Tests;
};