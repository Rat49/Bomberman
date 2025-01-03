#pragma once

#include "CollisionModule/CollisionComponent.hpp"
#include "CollisionModule/CollisionObject.hpp"
#include "CollisionModule/CollisionRectangle.hpp"
#include "CollisionModule/PhysicsModule.hpp"
#include "EventSystem/EventTypes.hpp"
#include "SpriteModule/Animation.hpp"
#include "SpriteModule/SpriteModule.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

enum class ObstacleType
{
    Unbreakable,
    Breakable
};

class Obstacle : public sf::Sprite, public CollisionObject
{
public:
    Obstacle(ObstacleType type, sf::Vector2f position, bool hasKeyOrGate = false);

    virtual ~Obstacle() = default;

    sf::Vector2f getPosition() const;

    ObstacleType getType() const;

    bool hasKeyOrGate() const;

    void setHasKeyOrGate(bool value);

    void changeAnim(sf::Vector2f obsPos);

    static bool isValidUnbreakablePosition(const sf::Vector2f& position);

    std::shared_ptr<Animation> getCurrentAnimation() const;

    CollisionComponent& getCollisionBox() const
    {
        return *collisionBox;
    }

    CollisionRectangle& getCollision()
    {
        return collision;
    }

    void initializeDestruction();

    bool hasExploded() const;

    void setCallbackID(EventID obstacleDestructionID);

private:
    ObstacleType obstacleType;
    sf::Vector2f obstaclePosition;

    int32_t currentAnimation = -1;
    int32_t idleBreakableObstacleAnimID;
    int32_t obstacleDestructionAnimID;

    float collisionBoxSize = 64.0f;

    // True if there is a key or gate under the obstacle
    bool obstacleHasKeyOrGate;

    EventID m_obstacleDestructionID = -1;

    CollisionRectangle collision;

    std::unique_ptr<CollisionComponent> collisionBox;

    bool m_hasExploded;
};
