#pragma once

#include "CollisionComponent.hpp"

class MockActor {
public:
	MockActor();
	~MockActor();

	//just for testing if parent pointer works
	void print();
	CollisionComponent* collisionBox;
};