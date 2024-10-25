#include "MockActor.hpp"
#include "Common/Logs.hpp"

MockActor::MockActor() {
	collisionBox = std::make_unique<CollisionComponent>();

	collisionBox->setParent(this);
}

void MockActor::print() {
	LOG("Hello from parent");
}