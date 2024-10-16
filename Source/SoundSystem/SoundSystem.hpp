#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include <vector>

class SoundSystem
{
public:
	bool loadSound(const std::string& soundName, const std::string& filePath);

	void playSound(const std::string& soundName);

private:
	// A map that associates a sound name with the corresponding Sound Buffer
	std::map<std::string, sf::SoundBuffer> soundBuffers;

	// A vector that stores instances of active sounds
	std::vector<sf::Sound> activeSounds;
};

