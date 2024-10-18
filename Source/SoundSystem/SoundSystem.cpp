#include "SoundSystem/SoundSystem.hpp"
#include "Common/Logs.hpp"
#include <iostream>

// SOUND
// Load audio and save to folder
bool SoundSystem::addSound(int32_t soundID, const std::string& filePath)
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(filePath)) 
	{
		LOG("Failed to load sound from %s", filePath.c_str());
		return false;
	}
	soundBuffers.emplace(soundID, std::move(buffer));
	LOG("Successfully loaded sound: %d", soundID);
	return true;
}

// Playing sound from the buffer
void SoundSystem::playSound(int32_t soundID)
{
	if (soundBuffers.find(soundID) != soundBuffers.end())
	{
		auto sound = std::make_unique<sf::Sound>();
		sound->setBuffer(soundBuffers[soundID]);
		sound->setVolume(100.f);
		sound->play();

		// Saving active sounds
		activeSounds.push_back({ soundID, std::move(sound) });
		LOG("Playing sound: %d", soundID);
	}
	else 
	{
		LOG("Sound %d not found!", soundID);
	}
}

// Stop sound
void SoundSystem::stopSound(int32_t soundID)
{
	for (auto it = activeSounds.begin(); it != activeSounds.end(); ++it)
	{
		if (it->first == soundID)
		{
			it->second->stop();
			LOG("Stopped sound: %d", soundID);
		}
	}
}

// Pause sound
void SoundSystem::pauseSound(int32_t soundID)
{
	for (auto& soundPair : activeSounds)
	{
		if (soundPair.first == soundID)
		{
			soundPair.second->pause();
			LOG("Paused sound: %d", soundID);
		}
	}
}

// Check if sound is playing
bool SoundSystem::isSoundPlaying(int32_t soundID) const
{
	for (const auto& soundPair : activeSounds)
	{
		if (soundPair.first == soundID && soundPair.second->getStatus() == sf::Sound::Playing)
		{
			return true;
		}
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
		LOG("Failed to load music from %s", filePath.c_str());
		return false;
	}
	musicTracks.emplace(musicID, std::move(music));
	LOG("Successfully loaded music: %d", musicID);
	return true;
}

// Play music
void SoundSystem::playMusic(int32_t musicID)
{
	auto it = musicTracks.find(musicID);
	if (it != musicTracks.end())
	{
		currentMusic = std::move(it->second);
		currentMusic->setVolume(100.f);
		currentMusic->play();
		LOG("Playing music: %d", musicID);
	}
	else
	{
		LOG("Music %d not found!", musicID);
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
