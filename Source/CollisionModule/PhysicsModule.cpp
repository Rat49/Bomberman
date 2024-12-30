#include "PhysicsModule.hpp"
#include "Common/FloatUtils.hpp"
#include "Common/Logs.hpp"
#include "GameModule/PlayerCharacter.hpp"

int PhysicsModule::ID = 0;

int PhysicsModule::registerObject(CollisionComponent* physicsObject)
{
	physicsObjects[ID] = physicsObject;
	return ID++;
}

void PhysicsModule::unRegisterObject(int id) {
	physicsObjects.erase(id);
}

void PhysicsModule::deleteObject(CollisionComponent* physicsObject)
{
    for (auto it = physicsObjects.begin(); it != physicsObjects.end(); ++it)
    {
        if (it->second == physicsObject)
        {
            physicsObjects.erase(it);
            return;
        }
    }
    LOG("Physics module - delete object failed (not found in map)");
}

void PhysicsModule::updateCollision()
{
    for (auto& it1: physicsObjects)
    {
        for (auto& it2: physicsObjects)
        {
            if (it1.first != it2.first)
                if (it1.second->update(*it2.second))
                    return;
        }
    }
}

//casts a ray and returns closest intersected object and its point of intersection
const CollisionComponent* PhysicsModule::rayCast(const sf::Vector2f& origin,
								const sf::Vector2f& direction,
								float maxDistance,
								sf::Vector2f& endPoint) {

	const CollisionComponent* candidate = nullptr;
	float minimumDistance = std::numeric_limits<float>::max();
	sf::Vector2f minEndPoint(origin + direction*maxDistance);

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

std::vector<std::pair<CollisionComponent*, sf::Vector2f>> PhysicsModule::rayCastAll(const sf::Vector2f& origin, const sf::Vector2f& direction, float maxDistance)
{
    std::vector<std::pair<CollisionComponent*, sf::Vector2f>> hitObjects;

	for (auto& iter : physicsObjects)
	{
		sf::Vector2f hitPoint;
		if (rayIntersectsRectangle(*iter.second, origin, direction, maxDistance, hitPoint))
		{
			hitObjects.emplace_back(iter.second, hitPoint);
		}
	}

	return hitObjects;
}

// Checks if ray intersects with rectangle
bool PhysicsModule::rayIntersectsRectangle(const CollisionRectangle& rectangle, 
										const sf::Vector2f& origin,
										const sf::Vector2f& direction,
										float maxDistance, 
										sf::Vector2f& endPoint) {

	sf::FloatRect bounds = rectangle.getRectangle().getGlobalBounds();

	if (bounds.contains(origin)) {
		return false;
	}
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

bool PhysicsModule::tryToMove()
{
    for (int i = 0; i < physicsObjects.size(); ++i)
    {
        if (dynamic_cast<PlayerCharacter*>(physicsObjects[i]->getObjectParent()))
        {
            for (int j = 0; j < physicsObjects.size(); ++j)
            {
				if (i != j)
				{
                    if (physicsObjects[i]->isOverlapping(*physicsObjects[j]))
                        return false;
				}
                   
            }
            return true;
        }
    }
    return true;
}
