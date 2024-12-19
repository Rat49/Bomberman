#pragma once

#include "CollisionModule/CollisionComponent.hpp"
#include "CollisionModule/CollisionObject.hpp"
#include "CollisionModule/CollisionRectangle.hpp"
#include "CollisionModule/PhysicsModule.hpp"
#include "Common/Modules.hpp"

class UnbreakableObstacle : public CollisionObject
{
public:
    UnbreakableObstacle(sf::Vector2f objPosition, sf::Vector2f collisionBoxSize);

    virtual ~UnbreakableObstacle() = default;

    CollisionComponent& getCollisionBox() const { return *collisionBox; }

    CollisionRectangle& getCollision() { return collision; }

private:
    std::unique_ptr<CollisionComponent> collisionBox;

    CollisionRectangle collision;

    int32_t collisionBoxID;
};
