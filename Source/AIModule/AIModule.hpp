#pragma once

#include <memory>
#include "FSM.hpp" 

// AIModule Class
class AIModule {
public:
	AIModule();

	// Called each frame to update the FSM
	void Update();

	// Example condition-checking methods, this is for advanced AI (if we go that route)
	bool IsPlayerInRange() const;
	bool IsBombNearby() const;

private:
	std::unique_ptr<FSM> fsm;
};