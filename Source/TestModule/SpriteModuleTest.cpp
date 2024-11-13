#include "SpriteModuleTest.hpp"
#include "SpriteModule/SpriteModule.hpp"
#include "SFML/Graphics.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"
#include <thread>
#include <chrono>

const std::string& SpriteModuleTest::getName() const
{
	return name;
}

void SpriteModuleTest::setup()
{	
	//create animation
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

void SpriteModuleTest::update(float deltaTime, sf::RenderWindow* window)
{
	window->setSize(sf::Vector2u(800, 600));

	Modules::Sprite->update(deltaTime, window); //update animation

	window->clear(sf::Color::Green);

	if (const auto& animation = Modules::Sprite->getAnimation(m_animationId))
	{
		if (animation->isPlaying())
		{
			window->draw(*animation); //draw animation
		}
	}
	window->display();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

bool SpriteModuleTest::isComplete() const
{
	return false;
}

