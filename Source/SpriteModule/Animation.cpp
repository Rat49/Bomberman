#include "Animation.hpp"
#include "Atlas.hpp"
#include <iostream>
#include <cstdint>


Animation::Animation(const std::string& configFilePath)
{
	//init atlas
	m_atlas = std::make_unique<Atlas>();
	if (!m_atlas->initialize(configFilePath))
		return;

	//set animation info
	m_isLooping = m_atlas->isLooping();
	m_frameDuration = m_atlas->getRenderDuration();

	//get atlas and rects
	for (const auto& [textureName, rects] : m_atlas->getAllTextureRects())
	{
		m_rects.push_back(rects);
	}
	m_atlasTexture = m_atlas->getAtlasTexture();
}

void Animation::Update(float deltaTime)
{
	if (!isPlaying())
		return;


	m_elapsedTime += deltaTime;

	//reset elapsed time for next frame and increase frame
	if (m_elapsedTime > m_frameDuration)
	{
		m_elapsedTime -= m_frameDuration;
		int32_t  previousFrame = m_currentFrame;
		m_currentFrame++;

		//check if its end of animation
		if (m_currentFrame >= static_cast<int32_t>(m_rects.size()))
		{
			if (m_isLooping)
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
			setTexture(*m_atlasTexture);
			setTextureRect(m_rects[m_currentFrame]);
		}
	}
}

void Animation::handleResize(const sf::Vector2f& scale)
{
	setPosition(sf::Vector2f(getPosition().x * scale.x, getPosition().y * scale.y));
	setScale(sf::Vector2f(getScale().x * scale.x, getScale().y * scale.y));
}

//play animation
void Animation::Play()
{
	m_isPlaying = true;
	m_currentFrame = 0;
	m_elapsedTime = 0;
	m_isStopped = false;
	// this had to be added, so that first frame is drawn
	setTexture(*m_atlasTexture);
	setTextureRect(m_rects[m_currentFrame]);
}

//stop animation
void Animation::Stop()
{
	m_isPlaying = false;
	m_elapsedTime = 0;
	m_isStopped = true;
}

void Animation::Resume()
{
	if (!m_isStopped)
	{
		m_isPlaying = true;
	}
}

void Animation::Pause()
{
	m_isPlaying = false;
}
