#pragma once
#include "AIModule/State.hpp"
#include <iostream>

class IdleState : public State {
public:
	void Enter(AIController* ai) override;

	void Update(AIController* ai) override;

	void Exit(AIController* ai) override;

	std::string GetName() const override { return "Idle"; }
};

class ChaseState : public State {
public:
	void Enter(AIController* ai) override;

	void Update(AIController* ai) override;

	void Exit(AIController* ai) override;

	std::string GetName() const override { return "Chase"; }
};