#include "GameModule/Obstacle.hpp"
#include <random>
#include <set>
#include <utility>
#include "Common/Modules.hpp"
#include "EventSystem/EventSystem.hpp"

Obstacle::Obstacle(ObstacleType type, sf::Vector2i position, bool hasKeyOrGate) : obstacleType(type), obstaclePosition(position), obstacleHasKeyOrGate(hasKeyOrGate) 
{
	m_obstacleDestructionID = Modules::Events->registerEvent();
}

sf::Vector2i Obstacle::getPosition() const
{
	return obstaclePosition;
}

ObstacleType Obstacle::getType() const
{
	return obstacleType;
}

bool Obstacle::hasKeyOrGate() const
{
	return obstacleHasKeyOrGate;
}

void Obstacle::setHasKeyOrGate(bool value)
{
	obstacleHasKeyOrGate = value;
}

bool Obstacle::isValidUnbreakablePosition(const sf::Vector2i& position)
{
	return position.x % 2 == 0 && position.y % 2 == 0;
}

void Obstacle::setCallbackID(EventID obstacleDestructionID)
{
	m_obstacleDestructionID = obstacleDestructionID;
}
