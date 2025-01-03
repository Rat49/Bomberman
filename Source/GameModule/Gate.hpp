#pragma once

#include "CollisionModule/CollisionComponent.hpp"
#include "CollisionModule/CollisionObject.hpp"
#include "CollisionModule/CollisionRectangle.hpp"
#include "CollisionModule/PhysicsModule.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Gate : public sf::Sprite, public CollisionObject
{
public:
    Gate(const sf::Vector2f& position);

    CollisionComponent& getCollisionBox() const
    {
        return *collisionBox;
    }

private:
    std::unique_ptr<CollisionComponent> collisionBox;

    int32_t collisionBoxID;

    float collisionBoxSize = 50.f;

    float gridSize = 64.f;
};
