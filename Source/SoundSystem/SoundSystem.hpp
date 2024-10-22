#pragma once

#include <SFML/Audio.hpp>
#include <map>
#include <memory>
#include <vector>
#include <random>
#include <string>

class SoundSystem
{
public:
	// SOUNDS: used for small sounds (gun shots, foot steps, etc.)

	// Loading sounds from the configuration file
	bool loadSoundsFromConfig(const std::string& configFilePath);

	// Adding a sound effect that can have multiple sounds
	bool addSoundEffect(int32_t soundID, const std::vector<std::string>& filePaths);

	void playSound(int32_t soundID);

	void stopSound(int32_t soundID);

	void pauseSound(int32_t soundID);

	bool isSoundPlaying(int32_t soundID) const;


	// MUSIC: used to play compressed music that lasts several minutes

	bool addMusic(int32_t musicID, const std::string& filePath);

	void playMusic(int32_t musicID);

	void stopMusic();

	void pauseMusic();

	bool isMusicPlaying() const;

private:
	//SOUNDS
	// Map that associates a soundID with a list of SoundBuffer objects
	std::map<int32_t, std::vector<sf::SoundBuffer>> soundEffectBuffers;

	// Map of active sounds, paired with their soundID
	std::map<int32_t, std::unique_ptr<sf::Sound>> activeSounds;

	// Random generator for choosing a random sound
	std::random_device randomDevice;
	std::mt19937 randomEngine{ randomDevice() };


	//MUSIC
	// Map that stores music for background music
	std::map<int32_t, std::shared_ptr<sf::Music>> musicTracks;

	// Shared pointer for the currently playing music
	std::shared_ptr<sf::Music> currentMusic;

};
