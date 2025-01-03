#include "OnliCollisionComponent.hpp"
#include "GameModule/Onli.hpp"
#include "Common/Logs.hpp"
void OnliCollisionComponent::BeginOverlapHandler(void* other)
{
    if (auto enemy = dynamic_cast<Onli*>(getObjectParent()))
    {
        auto otherComponent = static_cast<CollisionComponent*>(other);
        if (dynamic_cast<Obstacle*>(otherComponent->getObjectParent()))
        {
            enemy->swapDirections();
            enemy->setShouldChangeAnimation(true);
        }
    }
}

void OnliCollisionComponent::EndOverlapHandler(void*)
{
    return;
}