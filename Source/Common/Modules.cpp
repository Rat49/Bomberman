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
#include "CollisionModule/PhysicsModule.hpp"
#include "LevelHandlingModule/LevelHandlingModule.hpp"
#include "BaseModule/BaseModule.hpp"


#ifndef FINAL
std::unique_ptr<TestModule> Modules::Tests;
std::unique_ptr<LogManager> Modules::Logs;
#endif

GameModule* Modules::Game = nullptr;
EventSystem* Modules::Events = nullptr;
ConfigSystem* Modules::Config = nullptr;
NavigationModule* Modules::Navigation = nullptr;
SoundSystem* Modules::Sounds = nullptr;
InputModule* Modules::Input = nullptr;
SpriteModule* Modules::Sprite = nullptr;
UISystem* Modules::UI = nullptr;
AssetManager* Modules::Assets = nullptr;
PhysicsModule* Modules::Physics = nullptr;
LevelHandlingModule* Modules::Level = nullptr;

std::vector<std::unique_ptr<BaseModule>> Modules::modules = {};

bool Modules::initialize()
{
#ifndef FINAL
	Modules::Logs = std::make_unique<LogManager>();
	Modules::Tests = std::make_unique<TestModule>();
#endif

	// add your modules here
	Modules::Events = dynamic_cast<EventSystem*>(modules.emplace_back(std::make_unique<EventSystem>()).get());
	Modules::Config = dynamic_cast<ConfigSystem*>(modules.emplace_back(std::make_unique<ConfigSystem>()).get());
	Modules::Navigation = dynamic_cast<NavigationModule*>(modules.emplace_back(std::make_unique<NavigationModule>()).get());
	Modules::Sounds = dynamic_cast<SoundSystem*>(modules.emplace_back(std::make_unique<SoundSystem>()).get());
	Modules::Input = dynamic_cast<InputModule*>(modules.emplace_back(std::make_unique<InputModule>()).get());
	Modules::Sprite = dynamic_cast<SpriteModule*>(modules.emplace_back(std::make_unique<SpriteModule>()).get());
	Modules::UI = dynamic_cast<UISystem*>(modules.emplace_back(std::make_unique<UISystem>()).get());
	Modules::Assets = dynamic_cast<AssetManager*>(modules.emplace_back(std::make_unique<AssetManager>()).get());
	Modules::Physics = dynamic_cast<PhysicsModule*>(modules.emplace_back(std::make_unique<PhysicsModule>()).get());
	Modules::Level = dynamic_cast<LevelHandlingModule*>(modules.emplace_back(std::make_unique<LevelHandlingModule>()).get());

	Modules::Game = dynamic_cast<GameModule*>(modules.emplace_back(std::make_unique<GameModule>()).get());

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
