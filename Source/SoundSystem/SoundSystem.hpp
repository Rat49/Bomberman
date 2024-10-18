#pragma once

#include <SFML/Audio.hpp>
#include <map>
#include <list>
#include <memory>

class SoundSystem
{
public:
	// SOUNDS: used for small sounds (gun shots, foot steps, etc.)
	bool addSound(int32_t soundID, const std::string& filePath);

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
	// Map that stores sound buffers
	std::map<int32_t, sf::SoundBuffer> soundBuffers;

	// List of active sounds, paired with their soundID
	std::list<std::pair<int32_t, std::unique_ptr<sf::Sound>>> activeSounds;

	//MUSIC
	// Map that stores music for background music
	std::map<int32_t, std::unique_ptr<sf::Music>> musicTracks;

	// Unique pointer for the currently playing music
	std::unique_ptr<sf::Music> currentMusic;

};
