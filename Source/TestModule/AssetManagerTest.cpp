#include "AssetManagerTest.hpp"
#include "AssetManager/AssetManager.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"

const std::string& AssetManagerTest::getName() const
{
	return Name;
}

void AssetManagerTest::setup()
{
	LOG("AssetManagerTest: setup()");
	Modules::Assets->LoadAllAssets();
}

void AssetManagerTest::run()
{
	LOG("AssetManagerTest: run()");
	Modules::Assets->GetSound("bgSound");
}

void AssetManagerTest::update(float, sf::RenderWindow*)
{
	LOG("AssetManagerTest: update()");
}

bool AssetManagerTest::isComplete() const
{
	return true;
}