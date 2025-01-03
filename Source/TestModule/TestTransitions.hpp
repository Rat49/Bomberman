#pragma once

#include "AIModule/AIController.hpp"
#include "AIModule/Transition.hpp"

class IdleToChaseTransition : public Transition
{
public:
    IdleToChaseTransition(std::shared_ptr<State> targetState) : targetState(targetState)
    {
    }

    bool ShouldTrigger(AIController* ai) const override
    {
        return ai->getIsPlayerInRange();
    }

    std::shared_ptr<State> GetTargetState() const override
    {
        return targetState;
    }

private:
    std::shared_ptr<State> targetState;
};

class ChaseToIdleTransition : public Transition
{
public:
    ChaseToIdleTransition(std::shared_ptr<State> targetState) : targetState(targetState)
    {
    }

    bool ShouldTrigger(AIController* ai) const override
    {
        return !ai->getIsPlayerInRange();
    }

    std::shared_ptr<State> GetTargetState() const override
    {
        return targetState;
    }

private:
    std::shared_ptr<State> targetState;
};