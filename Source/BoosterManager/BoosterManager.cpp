#include "BoosterManager.hpp"
#include "Common/Logs.hpp"
bool BoosterManager::initialize(std::shared_ptr<PlayerCharacter> PlayerCharacter)
{
	m_playerCharacter = PlayerCharacter;
	return (!m_playerCharacter) ? false : true;
}

void BoosterManager::addBooster(std::shared_ptr<BoosterComponent> newBooster)
{
	if (m_boosters.find(newBooster->getBoosterID()) == m_boosters.end())
	{
		m_boosters[newBooster->getBoosterID()] = newBooster;
	}
	m_boosters[newBooster->getBoosterID()]->applyEffect(*m_playerCharacter);
}

void BoosterManager::update(float, sf::Window*) 
{
	std::map<int32_t, std::shared_ptr<BoosterComponent>>::iterator boostersIterator = m_boosters.begin();
	while (boostersIterator != m_boosters.end())
	{
		if (boostersIterator->second->shoulRemoveEffect())
		{
			if(boostersIterator->second->removeEffect(*m_playerCharacter))
			{
				boostersIterator = m_boosters.erase(boostersIterator);
				continue;
			}
		}
		++boostersIterator;
	}
}

void BoosterManager::removeAllBoosters()
{
	m_boosters.clear();
}

void BoosterManager::terminate()
{
	removeAllBoosters();
}