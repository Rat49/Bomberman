#include "SoundSystem/SoundSystem.hpp"
#include <iostream>

// Load audio and save to folder
bool SoundSystem::loadSound(const std::string& soundName, const std::string& filePath) 
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(filePath)) {
		std::cerr << "Failed to load sound from " << filePath << std::endl;
		return false;
	}
	soundBuffers[soundName] = buffer;
	return true;
}

// Playing sound from the buffer
void SoundSystem::playSound(const std::string& soundName) 
{
	if (soundBuffers.find(soundName) != soundBuffers.end()) 
	{
		sf::Sound sound;
		sound.setBuffer(soundBuffers[soundName]);
		sound.setVolume(100.f);
		sound.play();

		// Saving active sounds
		activeSounds.push_back(sound);
	}
	else 
	{
		std::cerr << "Sound " << soundName << " not found!" << std::endl;
	}
}