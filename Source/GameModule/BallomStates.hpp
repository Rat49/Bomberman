#pragma once
#include "AIModule/State.hpp"
#include "AIModule/Transition.hpp"
#include "AIModule/AIController.hpp"
#include <memory>
#include <random>
#include <chrono>
#include "Common/Logs.hpp"

class LookLeftState : public State
{
public:
    LookLeftState() : gen(rd()), d(0.5){}

    void Enter(AIController* ai) override;

    void Update(AIController* ai) override;

    void Exit(AIController* ai) override;

    std::string GetName() const override 
    { 
        return m_name; 
    }

private:
    const std::string m_name = "LookLeftState";
    std::chrono::steady_clock::time_point startTime;
    std::random_device rd;
    std::mt19937 gen;
    std::bernoulli_distribution d;
};

class LookRightState : public State
{
public:
    LookRightState() : gen(rd()), d(0.5) {}

    void Enter(AIController* ai) override;

    void Update(AIController* ai) override;

    void Exit(AIController* ai) override;

    std::string GetName() const override
    {
        return m_name;
    }

private:
    const std::string m_name = "LookRightState";
    std::chrono::steady_clock::time_point startTime;
    std::random_device rd;
    std::mt19937 gen;
    std::bernoulli_distribution d;
};

class LeftToRightTransition : public Transition
{
public:
    explicit LeftToRightTransition(std::shared_ptr<State> targetState) : targetState(std::move(targetState)) {}

    bool ShouldTrigger(AIController* ai) const override;

    std::shared_ptr<State> GetTargetState() const override;

private:
    std::shared_ptr<State> targetState;
};

class RightToLeftTransition : public Transition
{
public:
    explicit RightToLeftTransition(std::shared_ptr<State> targetState) : targetState(std::move(targetState)) {}

    bool ShouldTrigger(AIController* ai) const override;

    std::shared_ptr<State> GetTargetState() const override;

private:
    std::shared_ptr<State> targetState;
};
