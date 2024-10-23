#include "Animation.hpp"
#include "SpriteModule/Animation.hpp"
#include <iostream>
#include <cstdint>


//Problem with animation init
Animation::Animation(const std::string& configFilePath)
{
	//init atlas
	m_atlas = std::make_unique<Atlas>();
	if (!m_atlas->initialize(configFilePath))
		return;

	//set animation info
	m_info.m_isLooping = m_atlas->isLooping();
	m_info.m_frameDuration = m_atlas->getRenderDuration();

	//get atlas and rects
	for (const auto& [textureName, rects] : m_atlas->getAllTextureRects())
	{
		m_rects.push_back(rects);
	}
	m_textures.push_back(m_atlas->getTexture());

	m_sprite.setTexture(*m_textures[0]);
	m_sprite.setTextureRect(m_rects[0]);

}

void Animation::Update(float deltaTime)
{
	if (!isPlaying())
		return;


	m_elapsedTime += deltaTime;

	//reset elapsed time for next frame and increase frame
	if (m_elapsedTime > m_info.m_frameDuration)
	{
		m_elapsedTime -= m_info.m_frameDuration;
		int32_t  previousFrame = m_currentFrame;
		m_currentFrame++;

		//check if its end of animation
		if (m_currentFrame >= static_cast<int32_t>(m_rects.size()))
		{
			if (m_info.m_isLooping)
			{
				m_currentFrame = 0;
			}
			else
			{
				m_currentFrame = static_cast<int32_t>(m_rects.size() - 1); //keep last frame
				Stop();
			}

		}

		//set texture and rect
		if (previousFrame != m_currentFrame)
		{
			m_sprite.setTexture(*m_textures[0]);
			m_sprite.setTextureRect(m_rects[m_currentFrame]);
		}
	}
}

void Animation::Play()
{
	m_isPlaying = true;
	m_currentFrame = 0;
	m_elapsedTime = 0;
}

void Animation::Stop()
{
	m_isPlaying = false;
	m_elapsedTime = 0;
}
