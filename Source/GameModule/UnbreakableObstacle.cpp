#include "GameModule/UnbreakableObstacle.hpp"
#include <Common/Logs.hpp>

UnbreakableObstacle::UnbreakableObstacle(sf::Vector2f objPosition, sf::Vector2f collisionBoxSize)
{
    collision.setObjectParent(this);

    collisionBox = std::make_unique<CollisionComponent>();

    collisionBox->setObjectParent(this);

    collisionBox->setRectangleProperties(objPosition, collisionBoxSize);

    collisionBoxID = Modules::Physics->registerObject(collisionBox.get());

    Modules::Physics->addObject(collisionBox.get());
}
