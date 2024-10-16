#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include <list>
#include <memory>

class SoundSystem
{
public:
	bool loadSound(const std::string& soundName, const std::string& filePath);

	void playSound(const std::string& soundName);

	void stopSound(const std::string& soundName);

	void pauseSound(const std::string& soundName);

	bool isSoundPlaying(const std::string& soundName) const;

private:
	// Map that stores sound buffers
	std::map<std::string, sf::SoundBuffer> soundBuffers;

	// List of unique pointers to active sounds
	std::list<std::unique_ptr<sf::Sound>> activeSounds;
};

