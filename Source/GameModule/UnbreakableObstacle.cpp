#include "GameModule/UnbreakableObstacle.hpp"
#include <Common/Logs.hpp>

UnbreakableObstacle::UnbreakableObstacle(sf::Vector2f objPosition, sf::Vector2f collisionBoxSize)
{
    collisionBox = std::make_unique<CollisionComponent>();

    collisionBox->setObjectParent(this);

    collisionBox->setRectangleProperties(objPosition, collisionBoxSize);
}
