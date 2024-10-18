#include "Animation.hpp"
#include <iostream>
#include <cstdint>


//Problem with animation init
Animation::Animation(const std::string& atlasPath, const std::string& configFilePath, bool isLooping)
{
	//Do i need to create constructor for AnimationInfo?
	m_info.m_currentFrame = 0;
	m_info.m_elapsedTime = 0.f;
	m_info.m_isPlaying = false;
	m_info.m_isLooping = isLooping;

	//init atlas
	m_info.m_atlas = std::make_shared<Atlas>();
	if (!m_info.m_atlas->initialize(atlasPath, configFilePath))
		return;

	//how to init spriteInfo?

	//how to get the name for section? 
	m_info.m_atlas->initializeSprite("Walk1"); //for TEESTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT!!!!!!!!!!!!!!!!!!!!
}

void Animation::Update(float deltaTime)
{
	if (!isPlaying())
		return;


	m_info.m_elapsedTime += deltaTime;
	float currentFrameDuraton = m_info.m_spriteInfos[m_info.m_currentFrame].m_renderDuration;

	//reset elapsed time for next frame and increase frame
	if (m_info.m_elapsedTime > currentFrameDuraton)
	{
		m_info.m_elapsedTime -= currentFrameDuraton;
		int32_t  previousFrame = m_info.m_currentFrame;
		m_info.m_currentFrame++;

		//check if its end of animation
		if (m_info.m_currentFrame >= static_cast<int32_t>(m_info.m_spriteInfos.size()))
		{
			if (m_info.m_isLooping)
			{
				m_info.m_currentFrame = 0;
			}
			else
			{
				m_info.m_currentFrame = static_cast<int32_t>(m_info.m_spriteInfos.size() - 1); //keep last frame
				Stop();
			}

		}

		//set texture and rect
		if (previousFrame != m_info.m_currentFrame)
		{
			m_info.m_sprite->setTexture(*m_info.m_spriteInfos[m_info.m_currentFrame].m_texture);  
			m_info.m_sprite->setTextureRect(*m_info.m_spriteInfos[m_info.m_currentFrame].m_rect); //do i need to use sprite to change rects because i want do draw sprite on window
		}
	}
}

void Animation::Play()
{
	m_info.m_isPlaying = true;
	m_info.m_currentFrame = 0;
	m_info.m_elapsedTime = 0;
}

void Animation::Stop()
{
	m_info.m_isPlaying = false;
	m_info.m_elapsedTime = 0;
}
