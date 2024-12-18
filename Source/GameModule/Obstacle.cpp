#include "GameModule/Obstacle.hpp"
#include <random>
#include <set>
#include <utility>
#include "Common/Logs.hpp"

Obstacle::Obstacle(ObstacleType type, sf::Vector2i position, bool hasKeyOrGate) : obstacleType(type), obstaclePosition(position), obstacleHasKeyOrGate(hasKeyOrGate) {
    collisionBox = std::make_unique<CollisionComponent>();
    collisionBox->setParent(this);
    
    collisionBox->setRectangleProperties({static_cast<float>(position.x + 2), static_cast<float>(position.y + 2)}, {60.f,60.f});
    collisionBox->setColor(sf::Color::Blue);
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
