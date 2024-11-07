#pragma once

#include <memory>
#include "State.hpp"

class AIController;

//abstract class for transitions between states
class Transition {
public:
	virtual ~Transition() = default;
	
	//check if transition should be triggered
	virtual bool ShouldTrigger(AIController* ai) const = 0;

	//returns the state it should be transitioned to
	virtual std::shared_ptr<State> GetTargetState() const = 0;
};