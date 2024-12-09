#pragma once
#include <memory>
#include <vector>

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
class SpriteModule;
class UISystem;
class AssetManager;
class PhysicsModule;
class LevelHandlingModule;
class SaveSystem;
class BaseModule;

namespace sf {
	class Window;
}

/*
* This is a general manger class. Holder of all modules. You can access it from any part of the game
*/
struct Modules
{
	static bool initialize();
	static void terminate();
	static void update(float deltaTime, sf::Window* window);

#ifndef FINAL
	static std::unique_ptr<TestModule> Tests;
	static std::unique_ptr<LogManager> Logs;
#endif

	static GameModule* Game;
	static EventSystem* Events;
	static ConfigSystem* Config;
	static NavigationModule* Navigation;
	static SoundSystem* Sounds;
	static InputModule* Input;
	static SpriteModule* Sprite;
	static UISystem* UI;
	static AssetManager* Assets;
	static PhysicsModule* Physics;
	static LevelHandlingModule* Level;
	static SaveSystem* Save;

private:
	static std::vector<std::unique_ptr<BaseModule>> modules;
};
