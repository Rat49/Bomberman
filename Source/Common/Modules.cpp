#include "Common/Modules.hpp"
#include "GameModule/GameModule.hpp"
#include "TestModule/TestModule.hpp"
#include "LogModule/LogManager.hpp"
#include "EventSystem/EventSystem.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "NavigationModule/Navigation.hpp"
#include "SoundSystem/SoundSystem.hpp"
#include "InputModule/InputModule.hpp"
#include "SpriteModule/SpriteModule.hpp"
#include "UISystem/UISystem.hpp"
#include "AssetManager/AssetManager.hpp"
#include "BaseModule/BaseModule.hpp"


#ifndef FINAL
std::unique_ptr<TestModule> Modules::Tests;
std::unique_ptr<LogManager> Modules::Logs;
#endif

std::unique_ptr<GameModule> Modules::Game;
EventSystem* Modules::Events;
ConfigSystem* Modules::Config;
NavigationModule* Modules::Navigation;
SoundSystem* Modules::Sounds;
InputModule* Modules::Input;
SpriteModule* Modules::Sprite;
UISystem* Modules::UI;
AssetManager* Modules::Assets;

std::vector<std::unique_ptr<BaseModule>> Modules::modules = {};

bool Modules::initialize()
{
#ifndef FINAL
	Modules::Logs = std::make_unique<LogManager>();
	Modules::Tests = std::make_unique<TestModule>();
#endif

	Modules::Game = std::make_unique<GameModule>();
	
	// add your modules here
	Modules::Events = dynamic_cast<EventSystem*>(modules.emplace_back(std::make_unique<EventSystem>()).get());
	Modules::Config = dynamic_cast<ConfigSystem*>(modules.emplace_back(std::make_unique<ConfigSystem>()).get());
	Modules::Navigation = dynamic_cast<NavigationModule*>(modules.emplace_back(std::make_unique<NavigationModule>()).get());
	Modules::Sounds = dynamic_cast<SoundSystem*>(modules.emplace_back(std::make_unique<SoundSystem>()).get());
	Modules::Input = dynamic_cast<InputModule*>(modules.emplace_back(std::make_unique<InputModule>()).get());
	Modules::Sprite = dynamic_cast<SpriteModule*>(modules.emplace_back(std::make_unique<SpriteModule>()).get());
	Modules::UI = dynamic_cast<UISystem*>(modules.emplace_back(std::make_unique<UISystem>()).get());
	Modules::Assets = dynamic_cast<AssetManager*>(modules.emplace_back(std::make_unique<AssetManager>()).get());

	for (auto& module : modules) {
		if (!module->initialize()) {
			return false;
		}
	}
	return true;
}

void Modules::terminate()
{
	for (auto& module : modules) {
		module->terminate();
	}
	modules.clear();

	Modules::Game.release();

#ifndef FINAL
	Modules::Tests.release();
	Modules::Logs.release();
#endif
}

void Modules::update(float deltaTime, sf::Window* window)
{
	for (auto& module : modules) {
		module->update(deltaTime, window);
	}
}
