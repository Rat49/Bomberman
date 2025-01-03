#include "FSM.hpp"
#include "Common/Modules.hpp"
#include "GameModule/GameModule.hpp"

// The first state
void FSM::SetInitialState(std::shared_ptr<State> state) {
	currentState = state;
	currentState->Enter(owner);
}

// Add a transition from a state
void FSM::AddTransition(std::shared_ptr<State> from, std::shared_ptr<Transition> transition) {
	transitions[from].push_back(transition);
}

// Update to another state if some transition rules match
void FSM::Update() {
    // don't move if game is paused
    if (Modules::Game->getIsPaused())
		return;

	// Check transitions
	for (auto& transition : transitions[currentState]) {
		if (transition->ShouldTrigger(owner)) {
			currentState->Exit(owner);
			currentState = transition->GetTargetState();
			currentState->Enter(owner);
			return;
		}
	}
	// Update current state
	currentState->Update(owner);
}
