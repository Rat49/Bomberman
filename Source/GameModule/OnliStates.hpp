#pragma once
#include "AIModule/State.hpp"
#include "AIModule/Transition.hpp"
#include "AIModule/AIController.hpp"
#include <memory>
#include <random>
#include <chrono>
#include "Common/Logs.hpp"
#include <utility>
#include <unordered_map>
#include "CollisionModule/CollisionComponent.hpp"
#include "Onli.hpp"

class PatrollingState : public State
{
public:
    PatrollingState() : gen(rd()), d(0.5), directions({{1, 0}, {-1, 0}, {0, 1}, {0, -1}}) // right, left, down, up
    {
        m_directionPairs[Directions::Right] = Directions::Left;
        m_directionPairs[Directions::Left]  = Directions::Right;
        m_directionPairs[Directions::Down] = Directions::Up;
        m_directionPairs[Directions::Up]  = Directions::Down;
    }

    void Enter(AIController* ai) override;

    void Update(AIController* ai) override;

    void Exit(AIController* ai) override;

    std::string GetName() const override 
    { 
        return m_name; 
    }

private:
    const std::string m_name = "PatrollingState";
    std::chrono::steady_clock::time_point startTime;
    std::random_device rd;
    std::mt19937 gen;
    std::bernoulli_distribution d;
    std::vector<sf::Vector2f> directions;
    std::unordered_map<int8_t, int8_t> m_directionPairs;
};

class RestState : public State
{
public:
    RestState() : gen(rd()), d(0.5), directions({{1, 0}, {-1, 0}, {0, 1}, {0, -1}}) // right, left, down, up
    {
    }

    void Enter(AIController* ai) override;

    void Update(AIController* ai) override;

    void Exit(AIController* ai) override;

    std::string GetName() const override
    {
        return m_name;
    }

private:
    const std::string m_name = "RestState";
    std::chrono::steady_clock::time_point startTime;
    std::random_device rd;
    std::mt19937 gen;
    std::bernoulli_distribution d;
    std::vector<sf::Vector2f> directions;
};

class RestToPatrollingTransition : public Transition
{
public:
    explicit RestToPatrollingTransition(std::shared_ptr<State> targetState) : targetState(std::move(targetState))
    {
    }

    bool ShouldTrigger(AIController* ai) const override;

    std::shared_ptr<State> GetTargetState() const override;

private:
    std::shared_ptr<State> targetState;
};

class PatrollingToRestTransition : public Transition
{
public:
    explicit PatrollingToRestTransition(std::shared_ptr<State> targetState) : targetState(std::move(targetState))
    {
    }

    bool ShouldTrigger(AIController* ai) const override;

    std::shared_ptr<State> GetTargetState() const override;

private:
    std::shared_ptr<State> targetState;
};
