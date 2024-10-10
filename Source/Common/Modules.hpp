#pragma once
#include <memory>

#ifndef FINAL
class TestModule;
#endif

class GameModule;

/*
* This is a general manger class. Holder of all modules. You can access it from any part of the game
*/
struct Modules
{
	static void initialize();
	static void terminate();

#ifndef FINAL
	static std::unique_ptr<TestModule> Tests;
#endif
	static std::unique_ptr<GameModule> Game;
};