#pragma once
#include <memory>
#include "EnemyBase.hpp"

class EnemyFactory
{
public:
    static std::shared_ptr<EnemyBase> createEnemy(EnemyType type, sf::Vector2f spawnPosition,  std::vector<sf::Vector2i> patrollingPoints);
};
