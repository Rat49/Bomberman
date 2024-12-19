#include "OnliStates.hpp"
#include "Common/Logs.hpp"
#include "EnemyBase.hpp"
#include "CollisionModule/PhysicsModule.hpp"
#include "LevelHandlingModule/LevelHandlingModule.hpp"

namespace
{
    const int32_t RAYCAST_OFFSET = 32;
    const int32_t PARENT_OFFSET  = 64;
    const int32_t TILE_SIZE      = 64;
    const float RAYCAST_LENGTH   = 2.f;
    const int32_t ANIMATION_CHANGE_TIME = 2;
}

/*
 * look right state 
 */
void PatrollingState::Enter(AIController* ai)
{

    auto parent = static_cast<EnemyBase*>(ai->getParent());
    parent->playRightAnimation();
    startTime = std::chrono::steady_clock::now();
    sf::Vector2f collisionCenter = parent->getCollisionBox().getCenter();
    sf::Vector2i parentPosition  = {static_cast<int32_t>(parent->getPosition().x) / TILE_SIZE,
                                    static_cast<int32_t>(parent->getPosition().y) / TILE_SIZE};

    ai->setIsPlayerInRange(false);

    int8_t newDirection = 0;
    for (const auto& direction : directions)
    {
        sf::Vector2f endPoint;
        sf::Vector2f raycastStartingPos = {collisionCenter.x + (direction.x * RAYCAST_OFFSET),
                                           collisionCenter.y + (direction.y * RAYCAST_OFFSET)};

        bool isNotColiding = Modules::Physics->rayCast(raycastStartingPos, direction, RAYCAST_LENGTH, endPoint) == nullptr;
        isNotColiding &= Modules::Level->getTileInfo(parentPosition.x + static_cast<int32_t>(direction.x),
                                                     parentPosition.y + static_cast<int32_t>(direction.y)) == "Walkable";


        if (isNotColiding)
        {
            m_currentDirection = newDirection;
            break;
        }
        ++newDirection;
    }
}

void PatrollingState::Update(AIController* ai)
{

    auto parent  = static_cast<EnemyBase*>(ai->getParent());
    sf::Vector2f endPoint;
    sf::Vector2f collisionCenter = parent->getCollisionBox().getCenter();
    parent->getCollisionBox().setRectangleProperties(parent->getPosition(), {64.f, 64.f});
    sf::Vector2f parentPosition = parent->getPosition();
    sf::Vector2f raycastStartingPos = {collisionCenter.x + (directions[m_currentDirection].x * RAYCAST_OFFSET), 
                                       collisionCenter.y + (directions[m_currentDirection].y * RAYCAST_OFFSET)};
    sf::Vector2i parentPosition2     = {static_cast<int32_t>(parent->getPosition().x) / TILE_SIZE,
                                       static_cast<int32_t>(parent->getPosition().y) / TILE_SIZE};

    auto obstacleComponent = const_cast<CollisionComponent*>(Modules::Physics->rayCast(raycastStartingPos, directions[m_currentDirection], RAYCAST_LENGTH, endPoint));
    bool isNotColiding = obstacleComponent == nullptr;
    isNotColiding &= Modules::Level->getTileInfo((static_cast<int32_t>(collisionCenter.x + (directions[m_currentDirection].x * RAYCAST_OFFSET) ) ) / TILE_SIZE,
                                                 (static_cast<int32_t>(collisionCenter.y + (directions[m_currentDirection].y * RAYCAST_OFFSET) ) ) / TILE_SIZE) == "Walkable";

    if (isNotColiding)
    {
        parent->setPosition({parentPosition.x + (directions[m_currentDirection].x * parent->getVelocity()),
                             parentPosition.y + (directions[m_currentDirection].y * parent->getVelocity())});
    }
    else
    {
        m_currentDirection = m_directionPairs[m_currentDirection];
        m_changeAnimation  = true;
    }

    if (m_changeAnimation)
    {
        m_changeAnimation = false;
        switch (m_currentDirection)
        {
            case Directions::Right:
                parent->playRightAnimation();
                break;
            case Directions::Left:
                parent->playLeftAnimation();
                break;
            default:
                if (d(gen))
                {
                    parent->playLeftAnimation();
                }
                else
                {
                    parent->playRightAnimation();
                }
                break;
        }
    }
}

void PatrollingState::Exit(AIController*)
{
    return;
}

/*
 * look left state 
 */
void RestState::Enter(AIController* ai)
{
    auto parent = static_cast<EnemyBase*>(ai->getParent());
    sf::Vector2f collisionCenter = parent->getCollisionBox().getCenter();
    sf::Vector2i parentPosition  = {static_cast<int32_t>(parent->getPosition().x) / TILE_SIZE,
                                    static_cast<int32_t>(parent->getPosition().y) / TILE_SIZE};

    startTime = std::chrono::steady_clock::now();
    ai->setIsPlayerInRange(false);

    for (const auto& direction : directions)
    {
        sf::Vector2f endPoint;
        sf::Vector2f raycastStartingPos = {collisionCenter.x + (direction.x * RAYCAST_OFFSET),
                                           collisionCenter.y + (direction.y * RAYCAST_OFFSET)};

        bool isNotColiding = Modules::Physics->rayCast(raycastStartingPos, direction, RAYCAST_LENGTH, endPoint) == nullptr;
        isNotColiding &= Modules::Level->getTileInfo(parentPosition.x + static_cast<int32_t>(direction.x),
                                                     parentPosition.y + static_cast<int32_t>(direction.y)) == "Walkable";

        if (isNotColiding)
        {
            ai->setIsPlayerInRange(true);
            break;
        }
    }
}

void RestState::Update(AIController* ai)
{
    auto parent  = static_cast<EnemyBase*>(ai->getParent());
    sf::Vector2f collisionCenter = parent->getCollisionBox().getCenter();
    sf::Vector2i parentPosition  = {static_cast<int32_t>(parent->getPosition().x) / TILE_SIZE,
                                    static_cast<int32_t>(parent->getPosition().y) / TILE_SIZE};

    auto now     = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
    if (elapsed > 2)
    {
        for (const auto& direction : directions)
        {
            sf::Vector2f endPoint;
            sf::Vector2f raycastStartingPos = {collisionCenter.x + (direction.x * RAYCAST_OFFSET),
                                               collisionCenter.y + (direction.y * RAYCAST_OFFSET)};

            bool isNotColiding = Modules::Physics->rayCast(raycastStartingPos, direction, RAYCAST_LENGTH, endPoint) == nullptr;
            isNotColiding &= Modules::Level->getTileInfo(parentPosition.x + static_cast<int32_t>(direction.x),
                                                         parentPosition.y + static_cast<int32_t>(direction.y)) == "Walkable";

            if (isNotColiding)
            {
                ai->setIsPlayerInRange(true);
                break;
            }
        }

        if (d(gen))
        {
            parent->playLeftAnimation();
        }
        else
        {
            parent->playRightAnimation();
        }

         startTime = std::chrono::steady_clock::now();
    }
}

void RestState::Exit(AIController*)
{
    return;
}

/*
 * right to left state transition
 */
bool RestToPatrollingTransition::ShouldTrigger(AIController* ai) const
{
    return ai->getIsPlayerInRange();
}

std::shared_ptr<State> RestToPatrollingTransition::GetTargetState() const
{
    return targetState;
}

/*
 * left to right state transition
 */
bool PatrollingToRestTransition::ShouldTrigger(AIController* ai) const
{
    return ai->getIsPlayerInRange();
}

std::shared_ptr<State> PatrollingToRestTransition::GetTargetState() const
{
    return targetState;
}
