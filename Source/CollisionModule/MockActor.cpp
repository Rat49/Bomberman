#include "MockActor.hpp"
#include "Common/Logs.hpp"

MockActor::MockActor() {
	collisionBox = new CollisionComponent();

	collisionBox->setParent(this);
}
MockActor::~MockActor() {
	delete collisionBox;
}

void MockActor::print() {
	LOG("Hello from parent");
}