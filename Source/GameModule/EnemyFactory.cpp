#include "EnemyFactory.hpp"
#include "Common/Logs.hpp"
#include "Ballom.hpp"
#include "Onli.hpp"

std::shared_ptr<EnemyBase> EnemyFactory::createEnemy(EnemyType type, sf::Vector2f spawnPosition)
{
    switch (type)
    {
        case EnemyType::Basic:
        {
            auto enemy = std::make_shared<Onli>();
            enemy->initialize(type, spawnPosition);
            return enemy;
        }
        case EnemyType::Medium:
        {
            auto enemy = std::make_shared<Ballom>();
            enemy->initialize(type, spawnPosition);
            return enemy;
        }
        case EnemyType::Hard:
        {
            auto enemy = std::make_shared<Ballom>();
            enemy->initialize(type, spawnPosition);
            return enemy;
        }
        default:
            LOG("Unknown Enemy Type");
            return nullptr;
    }
}