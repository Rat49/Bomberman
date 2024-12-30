#pragma once
#include "CollisionComponent.hpp"

class PlayerCollisionComponent : public CollisionComponent
{
public:
    bool BeginOverlapHandler(void*) override;

    void EndOverlapHandler(void*) override;
};