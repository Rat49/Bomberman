#include "AIModule.hpp"

AIModule::AIModule(){
	// Initialize states

	// Set initial state

	// Add transitions
}

void AIModule::Update() {
	fsm->Update();
}

bool AIModule::IsPlayerInRange() const {
	// Example implementation for checking player proximity
	return true; 
}

bool AIModule::IsBombNearby() const {
	// Example implementation for checking bomb proximity
	return false; 
}