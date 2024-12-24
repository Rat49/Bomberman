#include "CollisionComponent.hpp"
#include "PhysicsModule.hpp"
#include "Common/Logs.hpp"
#include "Common/Modules.hpp"

CollisionComponent::CollisionComponent() :CollisionRectangle(){
	id = Modules::Physics->registerObject(this);
}
CollisionComponent::CollisionComponent(const sf::Vector2f& position, const sf::Vector2f& size) 
	:CollisionRectangle(position, size) {
	id = Modules::Physics->registerObject(this);
}

CollisionComponent::~CollisionComponent() {
	Modules::Physics->unRegisterObject(id);
}
//event handlers
//these will probably do something else but for now its just testing
void CollisionComponent::BeginOverlapHandler(void*) {
	LOG("Begin Overlap");
}

void CollisionComponent::EndOverlapHandler(void*) {
	LOG("End Overlap");
}
