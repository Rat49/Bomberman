#pragma once

#include "SFML/Graphics.hpp"
#include "SpriteModule/Sprite.hpp"
#include <vector>

class Atlas;

class Animation : public Sprite
{
public:

	//animation constructor
	Animation() = delete;
	Animation(const std::string& configFilePath);

	//functions for animation control
	void Play();
	void Stop();
	bool isPlaying() const { return m_isPlaying; }

	//function for updating animation
	void Update(float deltaTime);
	
private:
	
	//animation infos
	bool m_isLooping;
	float m_frameDuration;

	//state variables
	int32_t m_currentFrame = 0;
	float m_elapsedTime = 0;
	bool m_isPlaying = false;

	std::shared_ptr<sf::Texture> m_atlasTexture;
	std::vector<sf::IntRect> m_rects;
	std::unique_ptr<Atlas> m_atlas;
};

