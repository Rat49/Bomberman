#include "PhysicsModule.hpp"
#include "RayCast.hpp"

float distance(const sf::Vector2f& point1, const sf::Vector2f& point2) {
	float dx = point2.x - point1.x;
	float dy = point2.y - point1.y;
	return std::sqrt(dx * dx + dy * dy);
}

int PhysicsModule::ID = 0;

int PhysicsModule::registerObject(const CollisionComponent* physicsObject) {
	physicsObjects[ID] = physicsObject;
	return ID++;
}

void PhysicsModule::unRegisterObject(int id) {
	physicsObjects.erase(id);
}

//casts a ray and returns closest intersected object and its point of intersection
const CollisionComponent* PhysicsModule::CastARay(const sf::Vector2f& origin,
								const sf::Vector2f& direction,
								const float& maxDistance,
								sf::Vector2f& endPoint) {

	const CollisionComponent* candidate = nullptr;
	float minimumDistance = 2000.f;
	sf::Vector2f minEndPoint;

	std::unique_ptr<RayCast> ray = std::make_unique<RayCast>(origin, direction, maxDistance);

	//iterate over objects and find the nearest one that intersects with the ray
	for (auto& iter : physicsObjects) {
		if (ray->rayIntersectsRectangle(*iter.second, endPoint)) {
			float currentDistance = distance(origin, endPoint);
			if (minimumDistance > currentDistance) {
				minimumDistance = currentDistance;
				candidate = iter.second;
				minEndPoint = endPoint;
			}
		}
	}

	endPoint = minEndPoint;
	return candidate;
}