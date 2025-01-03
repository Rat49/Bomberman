#pragma once

#include "State.hpp"
#include "Transition.hpp"
#include <memory>
#include <unordered_map>

class AIController;

// Finite State Machine class used to handle all transitions between states and update current state
class FSM
{
public:
    FSM(AIController* owner) : owner(owner)
    {
    }

    // The first state
    void SetInitialState(std::shared_ptr<State> state);

    // Add a transition from a state
    void AddTransition(std::shared_ptr<State> from, std::shared_ptr<Transition> transition);

    // Update to another state if some transition rules match
    void Update();

private:
    // AI Controller
    AIController* owner;

    // Current state
    std::shared_ptr<State> currentState;

    // Map of transitions from states
    std::unordered_map<std::shared_ptr<State>, std::vector<std::shared_ptr<Transition>>> transitions;
};