#include "SoundSystem/SoundSystem.hpp"
#include "Common/Logs.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include <iostream>

// SOUND
// Load audio and save to folder
//bool SoundSystem::addSound(int32_t soundID, const std::string& filePath)
//{
//	sf::SoundBuffer buffer;
//	if (!buffer.loadFromFile(filePath)) 
//	{
//		LOG("Failed to load sound from $", filePath.c_str());
//		return false;
//	}
//	soundBuffers.emplace(soundID, std::move(buffer));
//	LOG("Successfully loaded sound: $", soundID);
//	return true;
//}


// Loading sounds from the configuration file
bool SoundSystem::loadSoundsFromConfig(const std::string& configFilePath)
{
	ConfigFile configFile(configFilePath, true);
	Modules::Config->addFile(configFile);

	// Initial ID for the effects
	int32_t soundID = 1;
	bool anySoundAdded = false;

	// Step through the sections for each sound, TEST
	std::vector<std::string> effects = { "WalkSound", "ExplosionSound" };

	for (const auto& effectName : effects)
	{
		if (!configFile.isSectionPresent(effectName))
			continue;

		std::vector<std::string> soundPaths;
		for (int i = 1; ; ++i)
		{
			// The prefix 'sound' is used this way because, in the 'ini' file, I have keys like 'sound1', 'sound2', 'sound3'
			std::string soundKey = "sound" + std::to_string(i);
			if (!configFile.getSection(effectName).isValuePresent(soundKey))
				break;

			std::string soundPath = configFile.getSection(effectName).getValue(soundKey).getString();
			soundPaths.push_back(soundPath);
		}

		if (!soundPaths.empty())
		{
			// Load sound files for this effect
			addSoundEffect(soundID++, soundPaths);
			anySoundAdded = true;
		}
	}

	return anySoundAdded;
}

// Adding a sound effect that can have multiple sounds
bool SoundSystem::addSoundEffect(int32_t soundID, const std::vector<std::string>&filePaths)
{
	std::vector<sf::SoundBuffer> buffers;
	for (const auto& filePath : filePaths)
	{
		sf::SoundBuffer buffer;
		if (!buffer.loadFromFile(filePath))
		{
			LOG("Failed to load sound from $", filePath.c_str());
			return false;
		}
		buffers.push_back(std::move(buffer));
	}

	soundEffectBuffers.emplace(soundID, std::move(buffers));
	LOG("Successfully loaded sound effect $", soundID);
	return true;
}

// Playing sound from the buffer
void SoundSystem::playSound(int32_t soundID)
{
	auto it = soundEffectBuffers.find(soundID);
	if (it != soundEffectBuffers.end() && !it->second.empty())
	{
		// Picking a random sound from a list
		const auto& buffers = it->second;
		std::uniform_int_distribution<size_t> dist(0, buffers.size() - 1);
		size_t randomIndex = dist(randomEngine);

		auto sound = std::make_unique<sf::Sound>();
		sound->setBuffer(buffers[randomIndex]);
		sound->setVolume(100.f);
		sound->play();

		// Saving active sounds
		activeSounds.emplace(soundID, std::move(sound));
		LOG("Playing sound:$", soundID);
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
