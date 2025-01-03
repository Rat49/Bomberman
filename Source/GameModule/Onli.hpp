#pragma once
#include "EnemyBase.hpp"
#include "CollisionModule/OnliCollisionComponent.hpp"

class PatrollingState;
class RestState;

enum Directions
{
    Right,
    Left,
    Down,
    Up
};

class Onli : public EnemyBase
{
public:
    Onli() : directions({{1, 0}, {-1, 0}, {0, 1}, {0, -1}})
    {
        m_currentDirection = Directions::Left;

        m_directionPairs[Directions::Right] = Directions::Left;
        m_directionPairs[Directions::Left]  = Directions::Right;
        m_directionPairs[Directions::Down]  = Directions::Up;
        m_directionPairs[Directions::Up]    = Directions::Down;
    }

    void initialize(EnemyType type, sf::Vector2f spawnPosition) override;

    void swapDirections();

    void setCurrentDirection(int8_t currentDirection)
    {
        m_currentDirection = currentDirection;
    }

    int32_t getCurrentDirection() const
    {
        return m_currentDirection;
    }

    CollisionComponent& getCollisionOnliBox() const
    {
        return *m_onliCollisionBox;
    }

    void setShouldChangeAnimation( bool shouldChangeAnimation)
    {
        m_shouldChangeAnimation = shouldChangeAnimation;
    }

    bool getShouldChangeAnimation()
    {
        return m_shouldChangeAnimation;
    }
private:
    std::shared_ptr<PatrollingState> patrollingState;
    std::shared_ptr<RestState> restState;

    std::vector<sf::Vector2f>          directions;
    int32_t                             m_currentDirection = Directions::Left;
    std::unordered_map<int32_t, int32_t> m_directionPairs;

    std::unique_ptr<OnliCollisionComponent> m_onliCollisionBox;

    bool m_shouldChangeAnimation = false;
};
