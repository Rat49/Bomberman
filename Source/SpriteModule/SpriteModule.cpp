#include "SpriteModule.hpp"


AnimationId SpriteModule::createAnimation(const std::string& configFilePath)
{
	animId++;
	m_animations[animId] = std::make_shared<Animation>(configFilePath);
	return animId;
}

std::shared_ptr<Animation> SpriteModule::getAnimation(AnimationId id) const
{
	auto animMap = m_animations.find(id);

	if (animMap == m_animations.end())
		return nullptr;

	return animMap->second;
}

void SpriteModule::update(float deltaTime)
{
	for (auto& pair : m_animations)
	{
		pair.second->Update(deltaTime); 
	}
}

// fill these methods 
bool SpriteModule::initialize()
{
	return true;
}

void SpriteModule::update(float, sf::Window*)
{
}

void SpriteModule::terminate()
{
}
