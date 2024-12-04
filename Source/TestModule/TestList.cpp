#include "TestModule/TestModule.hpp"
#include "Common/Modules.hpp"
//include your test file here
// -----------------------------
#include "TestModule/SampleTest.hpp"
#include "TestModule/WindowClosingTest.hpp"
#include "TestModule/ConfigSystemTest.hpp"
#include "TestModule/NavigationModuleTest.hpp"
#include "TestModule/InputModuleTest.hpp"
#include "TestModule/SpriteModuleTest.hpp"
#include "TestModule/CollisionModuleTest.hpp"
#include "TestModule/AssetManagerTest.hpp"
#include "TestModule/UILabelTest.hpp"
#include "TestModule/TestAI.hpp"
#include "TestModule/UIButtonTest.hpp"
#include "TestModule/PlayerTest.hpp"
#include "TestModule/LevelHandlingModuleTest.hpp"
#include "TestModule/UICheckboxTest.hpp"
#include "TestModule/UIInputFieldTest.hpp"
#include "TestModule/SoundSystemTest.hpp"

#include "TestFactoryCreator.hpp"

#include "TestRegisty.hpp"


#ifndef FINAL

bool TestRegisty::initialize()
{
	bool isEverythingInitialized = true;

	isEverythingInitialized &= registerFactory("SampleTest",std::make_shared<TestFactoryCreator<SampleTest>>());
	isEverythingInitialized &= registerFactory("WindowClosingTest",std::make_shared<TestFactoryCreator<WindowClosingTest>>());
	isEverythingInitialized &= registerFactory("ConfigSystemTest",std::make_shared<TestFactoryCreator<ConfigSystemTest>>());
	isEverythingInitialized &= registerFactory("InputModuleTest",std::make_shared<TestFactoryCreator<InputModuleTest>>());
	isEverythingInitialized &= registerFactory("AssetManagerTest",std::make_shared<TestFactoryCreator<AssetManagerTest>>());
	isEverythingInitialized &= registerFactory("TestAI",std::make_shared<TestFactoryCreator<TestAI>>());
	isEverythingInitialized &= registerFactory("CollisionModuleTest",std::make_shared<TestFactoryCreator<CollisionModuleTest>>());
	isEverythingInitialized &= registerFactory("NavigationModuleTest",std::make_shared<TestFactoryCreator<NavigationModuleTest>>());
	isEverythingInitialized &= registerFactory("SpriteModuleTest",std::make_shared<TestFactoryCreator<SpriteModuleTest>>());
	isEverythingInitialized &= registerFactory("UILabelTest",std::make_shared<TestFactoryCreator<UILabelTest>>());
	isEverythingInitialized &= registerFactory("UIButtonTest",std::make_shared<TestFactoryCreator<UIButtonTest>>());
	isEverythingInitialized &= registerFactory("PlayerTest",std::make_shared<TestFactoryCreator<PlayerTest>>());
	isEverythingInitialized &= registerFactory("LevelHandlingModuleTest",std::make_shared<TestFactoryCreator<LevelHandlingModuleTest>>());
	isEverythingInitialized &= registerFactory("SoundSystemTest",std::make_shared<TestFactoryCreator<SoundSystemTest>>());
	isEverythingInitialized &= registerFactory("UIInputFieldTest",std::make_shared<TestFactoryCreator<UIInputFieldTest>>());
	isEverythingInitialized &= registerFactory("UICheckboxTest", std::make_shared<TestFactoryCreator<UICheckboxTest>>());

	return isEverythingInitialized;
}

#endif