#include "GameModule/Gate.hpp"
#include "Common/Logs.hpp"

Gate::Gate(const sf::Vector2f& position)
{
    setPosition(position + sf::Vector2f((gridSize - collisionBoxSize) / 2, (gridSize - collisionBoxSize) / 2));

    collisionBox = std::make_unique<CollisionComponent>();

    collisionBox->setObjectParent(this);

    collisionBox->setRectangleProperties(getPosition(), sf::Vector2f(collisionBoxSize, collisionBoxSize));
}