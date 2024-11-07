#pragma once

#include "CollisionModule/CollisionComponent.hpp"
#include "AIModule/AIModule.hpp"
#include <memory>

class MockActor {
public:
	MockActor();
	~MockActor() {};

	//just for testing if parent pointer works
	void print();
	CollisionComponent& getCollisionBox() const { return *collisionBox; }
	AIController& getAIController() const { return *ai; }
private:
	std::unique_ptr<CollisionComponent> collisionBox;
	std::unique_ptr<AIController> ai;

};