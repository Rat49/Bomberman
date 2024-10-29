#include "AssetManagerTest.hpp"
#include "AssetManager/AssetManager.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"
#include "Common/StringUtils.hpp"

const std::string& AssetManagerTest::getName() const
{
	return Name;
}

void AssetManagerTest::setup()
{
	LOG("AssetManagerTest: setup()");
	Modules::Assets->initialize("../../Data/Config/assetmngr_config.ini");
	Modules::Assets->loadSound("Game/Sounds/bgSound.wav");
	Modules::Assets->loadSound("Game/Sounds/bgSound.wav");
	Modules::Assets->loadSound("Game/Sounds/bgSound.wav");
	Modules::Assets->loadSound("Game/Sounds/bgSound.wav");

	sf::SoundBuffer sb = *Modules::Assets->getSound("Game/Sounds/bgSound.wav");
}

void AssetManagerTest::run()
{
	LOG("AssetManagerTest: run()");
}

void AssetManagerTest::update(float, sf::RenderWindow*)
{
	LOG("AssetManagerTest: update()");
}

bool AssetManagerTest::isComplete() const
{
	return true;
}