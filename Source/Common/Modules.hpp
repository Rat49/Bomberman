#pragma once
#include <memory>

#ifndef FINAL
class TestModule;
class LogManager;
#endif

class GameModule;
class EventSystem;
class ConfigSystem;
class NavigationModule;
class SoundSystem;
class InputModule;
class QuestSystem;

/*
* This is a general manger class. Holder of all modules. You can access it from any part of the game
*/
struct Modules
{
	static void initialize();
	static void terminate();

#ifndef FINAL
	static std::unique_ptr<TestModule> Tests;
	static std::unique_ptr<LogManager> Logs;
#endif

	static std::unique_ptr<GameModule> Game;
	static std::unique_ptr<EventSystem> Events;
	static std::unique_ptr<ConfigSystem> Config;
	static std::unique_ptr<NavigationModule> Navigation;
	static std::unique_ptr<SoundSystem> Sounds;
	static std::unique_ptr<InputModule> Input;
	static std::unique_ptr<QuestSystem> Quests;
};
