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

	static std::unique_ptr<GameModule> Game;
	static std::unique_ptr<EventSystem> Events;
	static std::unique_ptr<ConfigSystem> Config;
	static std::unique_ptr<NavigationModule> Navigation;
	static std::unique_ptr<SoundSystem> Sounds;
	static std::unique_ptr<InputModule> Input;
	static std::unique_ptr<SpriteModule> Sprite;
	static std::unique_ptr<UISystem> UI;
	static std::unique_ptr<AssetManager> Assets;

private:
	static std::vector<std::unique_ptr<BaseModule>> modules;
};
