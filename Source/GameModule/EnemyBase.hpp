#pragma once
#include "AIModule/AIController.hpp"
#include "CollisionModule/CollisionComponent.hpp"
#include "GameModule/Obstacle.hpp"
#include "SpriteModule/Animation.hpp"
#include <SFML/System.hpp>
#include <vector>

class AIController;
class CollisionComponent;

enum class EnemyType
{
    Basic,
    Medium,
    Hard
};

class EnemyBase : public CollisionObject
{
public:
    EnemyBase() = default;

    virtual void initialize(EnemyType type, sf::Vector2f spawnPosition) = 0;

    EnemyType getType() const;

    sf::Vector2f getPosition() const;

    std::shared_ptr<Animation> getCurrentAnimation() const;

    void initializeDeath();

    void playLeftAnimation();

    void playRightAnimation();

    bool isDead() const;

    CollisionComponent& getCollisionBox() const
    {
        return *collisionBox;
    }

    AIController& getAIController() const
    {
        return *ai;
    }

    void setPosition(const sf::Vector2f& newPosition)
    {
        position = newPosition;
        getCurrentAnimation()->setPosition(position);
    }

    sf::Vector2f getPosition()
    {
        return position;
    }

    const std::vector<sf::Vector2i>& getPatrollingPoints()
    {
        return m_patrolligPoints;
    }

    void updateVelocity(float deltaTime);

    const float& getVelocity() const
    {
        return velocity;
    }

protected:
    EnemyType                 enemyType;
    sf::Vector2f              position;

    int32_t m_currentAnimationId = -1;
    int32_t m_deatAnimationId    = -1;
    int32_t m_leftAnimationId    = -1;
    int32_t m_rightAnimationId   = -1;

    bool isEnemyDead = false;

    std::unique_ptr<CollisionComponent> collisionBox;
    std::unique_ptr<AIController>       ai;

    std::vector<sf::Vector2i> m_patrolligPoints;

    float   speed = 0.0001f;
    float   velocity = 0.f;
};