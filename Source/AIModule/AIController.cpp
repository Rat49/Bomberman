#include "AIController.hpp"
#include "CollisionModule/PhysicsModule.hpp"
#include "Common/Modules.hpp"
#include "TestModule/MockActor.hpp"

AIController::AIController()
{
    fsm = std::make_unique<FSM>(this);
}

void AIController::Update()
{
    fsm->Update();
}

bool AIController::isBombNearby() const
{
    // Example implementation for checking bomb proximity
    return false;
}