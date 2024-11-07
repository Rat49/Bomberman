#pragma once

#include <memory>
#include "FSM.hpp" 
#include <SFML/Graphics.hpp>

// AIController Class
class AIController {
public:
	AIController();

	// Called each frame to update the FSM
	void Update();

	// Example condition-checking methods, this is for advanced AI (if we go that route)
	bool getIsPlayerInRange() const { return isPlayerInRange; }
	bool isBombNearby() const;

	// Getter for the parent
	void* getParent() const { return parentComponent; }

	// Setter for the parent
	void setParent(void* parent) { this->parentComponent = parent; }

	void setIsPlayerInRange(bool bIsPlayerInRange) { isPlayerInRange = bIsPlayerInRange; }
	std::unique_ptr<FSM> fsm;
private:
	void* parentComponent;
	bool isPlayerInRange;
	
};