#include "PlayerCollisionComponent.hpp"
#include "Common/Logs.hpp"
#include "GameModule/PlayerCharacter.hpp"
#include "GameModule/UnbreakableObstacle.hpp"
#include "GameModule/Booster.hpp"
#include "GameModule/EnemyBase.hpp"

void PlayerCollisionComponent::BeginOverlapHandler(void* other)
{
    if (auto player = dynamic_cast<PlayerCharacter*>(getObjectParent()))
    {
        auto otherComponent = static_cast<CollisionComponent*>(other);
        if (auto enemy = dynamic_cast<EnemyBase*>(otherComponent->getObjectParent()))
        {
            player->handleEnemyOverlap(enemy);
        }
        else if (dynamic_cast<Obstacle*>(otherComponent->getObjectParent()))
        {
            player->handleObstacleOverlap(true);
        }
        else if (dynamic_cast<UnbreakableObstacle*>(otherComponent->getObjectParent()))
        {
            player->handleObstacleOverlap(true);
        }
        else if (auto booster = dynamic_cast<Booster*>(otherComponent->getObjectParent()))
        {
            player->handleBoosterOverlap(booster);
        }
    }
}

void PlayerCollisionComponent::EndOverlapHandler(void* )
{
    
    
}
