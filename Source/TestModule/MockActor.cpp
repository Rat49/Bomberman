#include "MockActor.hpp"
#include "Common/Logs.hpp"

MockActor::MockActor()
{
    collisionBox = std::make_unique<CollisionComponent>();

    collisionBox->setParent(this);

    ai = std::make_unique<AIController>();

    ai->setParent(this);
}

void MockActor::print()
{
    LOG("Hello from parent");
}