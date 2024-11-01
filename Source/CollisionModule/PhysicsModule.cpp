#include "PhysicsModule.hpp"
#include "Common/FloatUtils.hpp"

int PhysicsModule::ID = 0;

int PhysicsModule::registerObject(const CollisionComponent* physicsObject) {
	physicsObjects[ID] = physicsObject;
	return ID++;
}

void PhysicsModule::unRegisterObject(int id) {
	physicsObjects.erase(id);
}

//casts a ray and returns closest intersected object and its point of intersection
const CollisionComponent* PhysicsModule::rayCast(const sf::Vector2f& origin,
								const sf::Vector2f& direction,
								float maxDistance,
								sf::Vector2f& endPoint) {

	const CollisionComponent* candidate = nullptr;
	float minimumDistance = std::numeric_limits<float>::max();
	sf::Vector2f minEndPoint;

	//iterate over objects and find the nearest one that intersects with the ray
	for (auto& iter : physicsObjects) {
		if (rayIntersectsRectangle(*iter.second, origin, direction, maxDistance, endPoint)) {
			float currentDistance = FloatUtils::squareDistance(origin, endPoint);
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

// Checks if ray intersects with rectangle
bool PhysicsModule::rayIntersectsRectangle(const CollisionRectangle& rectangle, 
										const sf::Vector2f& origin,
										const sf::Vector2f& direction,
										float maxDistance, 
										sf::Vector2f& endPoint) {

	sf::FloatRect bounds = rectangle.getRectangle().getGlobalBounds();

	sf::Vector2f temporary;
	// Horizontal Ray
	if (direction.x != 0) {
		float tx1 = (bounds.left - origin.x) / direction.x;
		float tx2 = (bounds.left + bounds.width - origin.x) / direction.x;

		float t = std::min(tx1, tx2);
		if (t >= 0 && t <= maxDistance) {
			temporary = origin + direction * t;
			if (temporary.y >= bounds.top && temporary.y <= bounds.top + bounds.height) {
				endPoint = temporary;
				return true;
			}
		}
	}

	if (direction.y != 0) {
		float ty1 = (bounds.top - origin.y) / direction.y;
		float ty2 = (bounds.top + bounds.height - origin.y) / direction.y;

		float t = std::min(ty1, ty2);
		if (t >= 0 && t <= maxDistance) {
			temporary = origin + direction * t;
			if (temporary.x >= bounds.left && temporary.x <= bounds.left + bounds.width) {
				endPoint = temporary;
				return true;
			}
		}
	}

	return false;  // No intersection
}

void PhysicsModule::terminate()
{
}
