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
#include "TestModule/LevelGeneratorTest.hpp"

#ifndef FINAL

void TestModule::CreateAllTests()
{
	// add your tests based on TestBase class here using this preset
	// Modules::Tests->addTest(std::make_shared<your-test-type>());
	// ----------------------------------------------------------------
	//Modules::Tests->addTest(std::make_shared<SampleTest>());
	//Modules::Tests->addTest(std::make_shared<WindowClosingTest>());
	//Modules::Tests->addTest(std::make_shared<ConfigSystemTest>());
	//Modules::Tests->addTest(std::make_shared<InputModuleTest>());
	//Modules::Tests->addTest(std::make_shared<AssetManagerTest>());
	//Modules::Tests->addTest(std::make_shared<TestAI>());
	//Modules::Tests->addTest(std::make_shared<CollisionModuleTest>());
	//Modules::Tests->addTest(std::make_shared<NavigationModuleTest>());
	//Modules::Tests->addTest(std::make_shared<SpriteModuleTest>());
	//Modules::Tests->addTest(std::make_shared<UILabelTest>());
	//Modules::Tests->addTest(std::make_shared<UIButtonTest>());
	//Modules::Tests->addTest(std::make_shared<PlayerTest>());
	//Modules::Tests->addTest(std::make_shared<LevelHandlingModuleTest>());
	Modules::Tests->addTest(std::make_shared<LevelGeneratorTest>());
}

#endif