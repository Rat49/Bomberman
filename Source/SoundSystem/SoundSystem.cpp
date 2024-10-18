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
		LOG("Failed to load sound from $", filePath.c_str());
		return false;
	}
	soundBuffers.emplace(soundID, std::move(buffer));
	LOG("Successfully loaded sound: $", soundID);
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
		currentMusic = std::shared_ptr<sf::Music>(std::move(it->second));
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
