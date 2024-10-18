#pragma once

#include "SFML/Graphics.hpp"
#include "SpriteModule/Sprite.hpp"
#include <vector>


struct AnimationInfo
{
	int32_t m_currentFrame;
	float m_elapsedTime;

	bool m_isPlaying;
	bool m_isLooping;

	std::vector<SpriteInfo> m_spriteInfos;

	std::shared_ptr<Atlas> m_atlas;
	std::shared_ptr<Sprite> m_sprite;

};

class Animation : public sf::Sprite
{
public:

	//create animation
	Animation() = delete;
	Animation(const std::string& atlasPath, const std::string& configFilePath, const bool isLooping /*, const float renderDuration */);

	//functions for animation control
	void Play();
	void Stop();
	bool isPlaying() const { return m_info.m_isPlaying; }

	//function for updating animation
	void Update(float deltaTime);
	
private:
	AnimationInfo m_info;
};

