#include "SoundSystemTest.hpp"
#include "AssetManager/AssetManager.hpp"
#include "Common/Logs.hpp"
#include "Common/Modules.hpp"
#include "SoundSystem/SoundSystem.hpp"

namespace
{
const std::string AssetPath       = "../../Data/Config/assetmngr_config.ini";
const std::string SoundCoinfgPath = "../../Data/Config/SoundTestConfig.ini";
} // namespace

const std::string& SoundSystemTest::getName() const
{
    return m_name;
}

void SoundSystemTest::setup()
{
    LOG("SOUND SYSTEM TEST SETUP");

    // load sound paths from config file and load sounds
    Modules::Sounds->loadSoundsFromConfig(SoundCoinfgPath);
}

void SoundSystemTest::run()
{
    LOG("SOUND SYSTEM TEST RUN");

    // play sound (one sound test)
    Modules::Sounds->playSound(3);

    // add music
    Modules::Sounds->addMusic(1, "Game/Sounds/bgSound.wav");

    //play music
    Modules::Sounds->playMusic(1);
}

void SoundSystemTest::update(float, sf::RenderWindow*)
{
}

bool SoundSystemTest::isComplete() const
{
    return false;
}
