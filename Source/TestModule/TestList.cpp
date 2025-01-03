#include "Common/Modules.hpp"
#include "TestModule/TestModule.hpp"
//include your test file here
// -----------------------------
#include "TestModule/AssetManagerTest.hpp"
#include "TestModule/CollisionModuleTest.hpp"
#include "TestModule/ConfigSystemTest.hpp"
#include "TestModule/InputModuleTest.hpp"
#include "TestModule/LevelGeneratorTest.hpp"
#include "TestModule/LevelHandlingModuleTest.hpp"
#include "TestModule/NavigationModuleTest.hpp"
#include "TestModule/PlayerTest.hpp"
#include "TestModule/SampleTest.hpp"
#include "TestModule/SaveSystemTest.hpp"
#include "TestModule/SoundSystemTest.hpp"
#include "TestModule/SpriteModuleTest.hpp"
#include "TestModule/TestAI.hpp"
#include "TestModule/UIButtonTest.hpp"
#include "TestModule/UICheckboxTest.hpp"
#include "TestModule/UIInputFieldTest.hpp"
#include "TestModule/UILabelTest.hpp"
#include "TestModule/UIProgressBarTest.hpp"
#include "TestModule/WindowClosingTest.hpp"
#include "TestRegisty.hpp"


#ifndef FINAL

bool TestRegisty::initialize()
{
    // add your tests based on TestBase class here using this preset
    // isEverythingInitialized &= registerTest<YourTest>("YourTest");
    // ----------------------------------------------------------------
    bool isEverythingInitialized = false;
    isEverythingInitialized &= registerTest<SampleTest>("SampleTest");
    isEverythingInitialized &= registerTest<WindowClosingTest>("WindowClosingTest");
    isEverythingInitialized &= registerTest<ConfigSystemTest>("ConfigSystemTest");
    isEverythingInitialized &= registerTest<InputModuleTest>("InputModuleTest");
    isEverythingInitialized &= registerTest<TestAI>("TestAI");
    isEverythingInitialized &= registerTest<CollisionModuleTest>("CollisionModuleTest");
    isEverythingInitialized &= registerTest<NavigationModuleTest>("NavigationModuleTest");
    isEverythingInitialized &= registerTest<SpriteModuleTest>("SpriteModuleTest");
    isEverythingInitialized &= registerTest<UILabelTest>("UILabelTest");
    isEverythingInitialized &= registerTest<UIButtonTest>("UIButtonTest");
    isEverythingInitialized &= registerTest<PlayerTest>("PlayerTest");
    isEverythingInitialized &= registerTest<LevelHandlingModuleTest>("LevelHandlingModuleTest");
    isEverythingInitialized &= registerTest<SoundSystemTest>("SoundSystemTest");
    isEverythingInitialized &= registerTest<UIInputFieldTest>("UIInputFieldTest");
    isEverythingInitialized &= registerTest<AssetManagerTest>("AssetManagerTest");
    isEverythingInitialized &= registerTest<LevelGeneratorTest>("LevelGeneratorTest");
    isEverythingInitialized &= registerTest<UIProgressBarTest>("UIProgressBarTest");
    isEverythingInitialized &= registerTest<SaveSystemTest>("SaveSystemTest");
    isEverythingInitialized &= registerTest<UICheckboxTest>("UICheckboxTest");
    return isEverythingInitialized;
}

#endif