#pragma once

#include <string>

class AIModule;

//abstract class used for deriving other states
class State {
public:
	virtual ~State() = default;

	// Called when entering the state
	virtual void Enter(AIModule* ai) = 0;

	// Called every frame to update the state
	virtual void Update(AIModule* ai) = 0;

	// Called when exiting the state
	virtual void Exit(AIModule* ai) = 0;

	virtual std::string GetName() const = 0;
};