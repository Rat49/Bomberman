#include "EnemyFactory.hpp"
#include "Ballom.hpp"
#include "Common/Logs.hpp"
#include "Dahl.hpp"
#include "Onli.hpp"

std::shared_ptr<EnemyBase> EnemyFactory::createEnemy(EnemyType                                       type,
                                                     sf::Vector2f                                    spawnPosition,
                                                     std::shared_ptr<std::vector<std::vector<bool>>> navGrid)
{
    switch (type)
    {
        case EnemyType::Basic:
        {
            auto enemy = std::make_shared<Ballom>();
            enemy->initialize(type, spawnPosition);
            return enemy;
        }
        case EnemyType::Medium:
        {
            auto enemy = std::make_shared<Onli>();
            enemy->initialize(type, spawnPosition);
            return enemy;
        }
        case EnemyType::Hard:
        {
            auto enemy = std::make_shared<Dahl>();
            enemy->initialize(type, spawnPosition);
            enemy->initialzieNavModule(navGrid);
            return enemy;
        }
        default:
            LOG("Unknown Enemy Type");
            return nullptr;
    }
}