#include "SoundSystem/SoundSystem.hpp"
#include "Common/Logs.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include <random>
#include <iostream>

// SOUND
// Load audio and save to folder
bool SoundSystem::addSound(int32_t soundID, const std::string& filePath)
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(filePath))
	{
		LOG("Failed to load sound from $", filePath.c_str());
		return false;
	}
	soundEffectBuffers[soundID].emplace_back(std::move(buffer));
	LOG("Successfully loaded sound: $", soundID);
	return true;
}


// Loading sounds from the configuration file
bool SoundSystem::loadSoundsFromConfig(const std::string& configFilePath)
{
	ConfigFile configFile(configFilePath, true);
	Modules::Config->addFile(configFile);

	// Initial ID for the effects
	int32_t soundID = 1;
	bool anySoundAdded = false;

	// This part is commented out for now because I don't have a method like getAllSections(), but once Tijana adds it, I will use it here like this
	/*
	// Step through all sections in the config file
	auto sectionNames = configFile.getAllSections();

	for (const auto& effectName : sectionNames)
	{
		std::vector<std::string> filePaths;

		// Iterate through keys in the section to gather all sound file paths
		int32_t i = 1;
		while (configFile.getSection(effectName).isValuePresent("sound" + std::to_string(i)))
		{
			filePaths.push_back(configFile.getSection(effectName).getValue("sound" + std::to_string(i)).getString());
			i++;
		}

		if (!filePaths.empty())
		{
			addSoundEffect(soundID++, filePaths);
			anySoundAdded = true;
		}
	}
	*/

	return anySoundAdded;
}

// Adding a sound effect that can have multiple sounds
bool SoundSystem::addSounds(int32_t soundID, const std::list<std::string>&filePaths)
{
	// Check if a sound with the same ID already exists
	if (soundEffectBuffers.find(soundID) != soundEffectBuffers.end())
	{
		LOG("Sound effect with ID $ already exists!", soundID);
		return false; 
	}

	// Loading sound files
	for (const auto& filePath : filePaths)
	{
		if (!addSound(soundID, filePath))
		{
			LOG("Failed to load sound from $", filePath.c_str());
			return false;
		}
	}

	LOG("Successfully loaded sound effect $", soundID);
	return true;
}

// Playing sound from the buffer
void SoundSystem::playSound(int32_t soundID)
{
	auto it = soundEffectBuffers.find(soundID);
	if (it != soundEffectBuffers.end() && !it->second.empty())
	{
		const auto& buffers = it->second;

		// Check if there's only one buffer
		if (buffers.size() == 1)
		{
			auto sound = std::make_unique<sf::Sound>();
			sound->setBuffer(buffers.front());
			sound->setVolume(100.f);
			sound->play();

			// Saving active sounds
			activeSounds.emplace(soundID, std::move(sound));
			LOG("Playing single sound: $", soundID);
		}
		// More than one sound, pick a random one
		else
		{
			// Create generator and distribution locally
			std::random_device randomDevice;
			std::mt19937 randomEngine{ randomDevice() };
			std::uniform_int_distribution<size_t> dist(0, std::distance(buffers.begin(), buffers.end()) - 1);
			auto randomIt = std::next(buffers.begin(), dist(randomEngine));

			auto sound = std::make_unique<sf::Sound>();
			// Use random buffer
			sound->setBuffer(*randomIt);
			sound->setVolume(100.f);
			sound->play();

			// Saving active sounds
			activeSounds.emplace(soundID, std::move(sound));
			LOG("Playing sound:$", soundID);
		}
	}
	else 
	{
		LOG("Sound $ not found!", soundID);
	}
}

// Stop sound
void SoundSystem::stopSound(int32_t soundID)
{
	auto it = activeSounds.find(soundID);
	if (it != activeSounds.end())
	{
		it->second->stop();
		LOG("Stopped sound: $", soundID);
	}
	else 
	{
		LOG("Sound $ not found!", soundID);
	}
}

// Pause sound
void SoundSystem::pauseSound(int32_t soundID)
{
	auto it = activeSounds.find(soundID);
	if (it != activeSounds.end())
	{
		it->second->pause();
		LOG("Paused sound: $", soundID);
	}
	else
	{
		LOG("Sound $ not found!", soundID);
	}
}

// Check if sound is playing
bool SoundSystem::isSoundPlaying(int32_t soundID) const
{
	auto it = activeSounds.find(soundID);
	if (it != activeSounds.end())
	{
		return it->second->getStatus() == sf::Sound::Playing;
	}
	return false;
}

// MUSIC
// Load music from file and store it
bool SoundSystem::addMusic(int32_t musicID, const std::string& filePath)
{
	auto music = std::make_unique<sf::Music>();
	if (!music->openFromFile(filePath))
	{
		LOG("Failed to load music from $", filePath.c_str());
		return false;
	}
	musicTracks.emplace(musicID, std::move(music));
	LOG("Successfully loaded music: $", musicID);
	return true;
}

// Play music
void SoundSystem::playMusic(int32_t musicID)
{
	auto it = musicTracks.find(musicID);
	if (it != musicTracks.end())
	{
		currentMusic = it->second;
		currentMusic->setVolume(100.f);
		currentMusic->play();
		LOG("Playing music: $", musicID);
	}
	else
	{
		LOG("Music $ not found!", musicID);
	}
}

// Stop music
void SoundSystem::stopMusic()
{
	if (currentMusic)
	{
		currentMusic->stop();
		LOG("Stopped music");

		// Clear current music after stopping
		currentMusic.reset();
	}
}

// Pause music
void SoundSystem::pauseMusic()
{
	if (currentMusic)
	{
		currentMusic->pause();
		LOG("Paused music");
	}
}

// Check if music is playing
bool SoundSystem::isMusicPlaying() const
{
	return currentMusic && currentMusic->getStatus() == sf::Music::Playing;
}
