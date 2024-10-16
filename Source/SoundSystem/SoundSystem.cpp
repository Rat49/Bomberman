#include "SoundSystem/SoundSystem.hpp"
#include "Common/Logs.hpp"
#include <iostream>

// Load audio and save to folder
bool SoundSystem::loadSound(const std::string& soundName, const std::string& filePath) 
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(filePath)) 
	{
		LOG("Failed to load sound from %s", filePath.c_str());
		return false;
	}
	soundBuffers.emplace(soundName, std::move(buffer));
	LOG("Successfully loaded sound: %s", soundName.c_str());
	return true;
}

// Playing sound from the buffer
void SoundSystem::playSound(const std::string& soundName) 
{
	if (soundBuffers.find(soundName) != soundBuffers.end()) 
	{
		auto sound = std::make_unique<sf::Sound>();
		sound->setBuffer(soundBuffers[soundName]);
		sound->setVolume(100.f);
		sound->play();

		// Saving active sounds
		activeSounds.push_back(std::move(sound));
		LOG("Playing sound: %s", soundName.c_str());
	}
	else 
	{
		LOG("Sound %s not found!", soundName.c_str());
	}
}

// Stop sound
void SoundSystem::stopSound(const std::string& soundName)
{
	for (auto& sound : activeSounds) 
	{
		if (sound->getBuffer() == &soundBuffers[soundName]) 
		{
			sound->stop();
			LOG("Stopped sound: %s", soundName.c_str());
		}
	}
}

// Pause sound
void SoundSystem::pauseSound(const std::string& soundName)
{
	for (auto& sound : activeSounds) 
	{
		if (sound->getBuffer() == &soundBuffers[soundName]) 
		{
			sound->pause();
			LOG("Paused sound: %s", soundName.c_str());
		}
	}
}

// Check if sound is playing
bool SoundSystem::isSoundPlaying(const std::string& soundName) const
{
	auto it = soundBuffers.find(soundName);
	if (it == soundBuffers.end()) 
	{
		return false;
	}

	for (const auto& sound : activeSounds) 
	{
		if (sound->getBuffer() == &it->second && sound->getStatus() == sf::Sound::Playing) 
		{
			return true;
		}
	}
	return false;
}
