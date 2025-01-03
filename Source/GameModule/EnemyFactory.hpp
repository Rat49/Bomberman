#pragma once
#include "EnemyBase.hpp"
#include <memory>

class EnemyFactory
{
public:
    static std::shared_ptr<EnemyBase> createEnemy(EnemyType                                       type,
                                                  sf::Vector2f                                    spawnPosition,
                                                  std::shared_ptr<std::vector<std::vector<bool>>> navGrid);
};
