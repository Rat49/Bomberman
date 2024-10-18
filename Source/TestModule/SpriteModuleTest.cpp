#include "SpriteModuleTest.hpp"
#include "SpriteModule/SpriteModule.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"

const std::string& SpriteModuleTest::getName() const
{
	return name;
}

void SpriteModuleTest::setup()
{
	//create animation and get animation id 
	m_animationId = Modules::Sprite->createAnimation("../../Assets/Textures/general.png", "../../Data/Config/WalkingAnimation.ini", true);
}

void SpriteModuleTest::run()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Animation Test");

	//get animation and play
	if (const auto& animation = Modules::Sprite->getAnimation(m_animationId))
	{
		animation->Play();
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		} 

		if (const auto& animation = Modules::Sprite->getAnimation(m_animationId))
		{
			if (animation->isPlaying())
			{
				window.clear();
				//window.draw(*animation); //or sprite
				window.display();
			}
		}
	}
}


void SpriteModuleTest::update(float deltaTime)
{
	Modules::Sprite->update(deltaTime);
}

bool SpriteModuleTest::isComplete() const
{
	return true;
}

