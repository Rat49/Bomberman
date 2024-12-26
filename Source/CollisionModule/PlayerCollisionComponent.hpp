#pragma once
#include "CollisionComponent.hpp"

class PlayerCollisionComponent : public CollisionComponent
{
public:
    void BeginOverlapHandler(void*) override;

    void EndOverlapHandler(void*) override;
};