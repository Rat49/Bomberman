#pragma once
#include "CollisionComponent.hpp"

class OnliCollisionComponent : public CollisionComponent
{
public:
    void BeginOverlapHandler(void* other) override;

    void EndOverlapHandler(void*) override;
};
