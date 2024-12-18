#pragma once
#include "EnemyBase.hpp"

class PatrollingState;
class RestState;

class Onli : public EnemyBase
{
public:
    Onli() = default;

    void initialize(EnemyType type, sf::Vector2f spawnPosition, std::vector<sf::Vector2i> patrollingPoints) override;

private:
    std::shared_ptr<PatrollingState> patrollingState;
    std::shared_ptr<RestState> restState;
};
