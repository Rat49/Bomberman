#pragma once
#include "AIModule/AIController.hpp"
#include "AIModule/State.hpp"
#include "AIModule/Transition.hpp"
#include "Common/Logs.hpp"
#include <chrono>
#include <memory>
#include <random>
#include <unordered_map>
#include <utility>
#include "Dahl.hpp"

enum Directions
{
    Right,
    Left,
    Down,
    Up
};

class FollowState : public State
{
public:
    FollowState() : m_gen(m_rd()), m_d(0.5) {}

    void Enter(AIController* ai) override;

    void Update(AIController* ai) override;

    void Exit(AIController* ai) override;

    std::string GetName() const override
    {
        return m_name;
    }

private:
    void switchAnimation(Dahl* parent);

private:
    const std::string m_name = "FollowState";
    std::chrono::steady_clock::time_point m_startTime;
    std::random_device m_rd;
    std::mt19937 m_gen;
    std::bernoulli_distribution m_d;

    bool m_changeAnimation = true;

    sf::Vector2i m_moveTo;
    sf::Vector2i m_currentPos;

    sf::Vector2f m_dir;
    sf::Vector2f m_currentDir;
};

class StandbyState : public State
{
public:
    StandbyState() : gen(rd()), d(0.5), directions({{1, 0}, {-1, 0}, {0, 1}, {0, -1}}) // right, left, down, up
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
    const std::string                     m_name = "StandbyState";
    std::chrono::steady_clock::time_point startTime;
    std::random_device                    rd;
    std::mt19937                          gen;
    std::bernoulli_distribution           d;
    std::vector<sf::Vector2f>             directions;
};

class FollowToStandbyStateTransition : public Transition
{
public:
    explicit FollowToStandbyStateTransition(std::shared_ptr<State> targetState) : targetState(std::move(targetState))
    {
    }

    bool ShouldTrigger(AIController* ai) const override;

    std::shared_ptr<State> GetTargetState() const override;

private:
    std::shared_ptr<State> targetState;
};

class StandbyToFollowStateTransition : public Transition
{
public:
    explicit StandbyToFollowStateTransition(std::shared_ptr<State> targetState) : targetState(std::move(targetState))
    {
    }

    bool ShouldTrigger(AIController* ai) const override;

    std::shared_ptr<State> GetTargetState() const override;

private:
    std::shared_ptr<State> targetState;
};
