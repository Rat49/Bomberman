#pragma once

#include <string>

class AIController;

//abstract class used for deriving other states
class State {
public:
	virtual ~State() = default;

	// Called when entering the state
	virtual void Enter(AIController* ai) = 0;

	// Called every frame to update the state
	virtual void Update(AIController* ai) = 0;

	// Called when exiting the state
	virtual void Exit(AIController* ai) = 0;

	virtual std::string GetName() const = 0;
};