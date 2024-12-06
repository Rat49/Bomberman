#include "GameModule/Obstacle.hpp"
#include <random>
#include <set>
#include <utility>

Obstacle::Obstacle() {}

Obstacle::Obstacle(ObstacleType type, sf::Vector2i position, bool hasKeyOrGate) : obstacleType(type), obstaclePosition(position), obstacleHasKeyOrGate(hasKeyOrGate)
{
	collisionBox = std::make_unique<CollisionComponent>();

	collisionBox->setParent(this);

	collisionBox->setRectangleProperties(sf::Vector2f((float)getPosition().x, (float)getPosition().y), sf::Vector2f(52.0f, 52.0f));
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
	return position.x % 2 == 0 && position.y % 2 == 0;;
}
