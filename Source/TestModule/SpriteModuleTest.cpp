#include "SpriteModuleTest.hpp"
#include "SpriteModule/SpriteModule.hpp"
#include "SFML/Graphics.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"

const std::string& SpriteModuleTest::getName() const
{
	return name;
}

void SpriteModuleTest::setup()
{
	m_window.create(sf::VideoMode(800, 600), "Animation Test");
	//create animation and get animation id 
	m_animationId = Modules::Sprite->createAnimation("../../Data/Config/WalkingAnimation.ini");
}

void SpriteModuleTest::run()
{
	//get animation and play
	if (const auto& animation = Modules::Sprite->getAnimation(m_animationId))
	{
		animation->Play();	
	}
}


void SpriteModuleTest::update(float deltaTime)
{
	//deltaTime++;
	Modules::Sprite->update(deltaTime);


	if (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
		}

		m_window.clear();

		if (const auto& animation = Modules::Sprite->getAnimation(m_animationId))
		{
			if (animation->isPlaying())
			{
				m_window.draw(animation->getCurrentSprite());
			}
		}

		m_window.display();
	}
}

bool SpriteModuleTest::isComplete() const
{
	return false;
}

