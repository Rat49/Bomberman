#pragma once

#include "SFML/Graphics.hpp"
#include "SpriteModule/Sprite.hpp"
#include <vector>


struct AnimationInfo
{
	bool m_isLooping;
	float m_frameDuration;
};

class Animation : public sf::Sprite
{
public:

	//create animation
	Animation() = delete;
	Animation(const std::string& configFilePath);

	//functions for animation control
	void Play();
	void Stop();
	bool isPlaying() const { return m_isPlaying; }

	//function for updating animation
	void Update(float deltaTime);

	const sf::Sprite& getCurrentSprite() const { return m_sprite; }
	
private:
	AnimationInfo m_info;

	//state variables
	int32_t m_currentFrame = 0;
	float m_elapsedTime = 0;
	bool m_isPlaying = false;

	std::vector<std::shared_ptr<sf::Texture>> m_textures;
	std::vector<sf::IntRect> m_rects;

	std::unique_ptr<Atlas> m_atlas;
	sf::Sprite m_sprite;
};

