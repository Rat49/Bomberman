#include "CollisionComponent.hpp"
#include "Common/Logs.hpp"

//event handlers
//these will probably do something else but for now its just testing
void CollisionComponent::BeginOverlapHandler(void*) {
	LOG("Begin Overlap");
}

void CollisionComponent::EndOverlapHandler(void*) {
	LOG("End Overlap");
}