#pragma once
#include <unordered_map>
#include <memory>
#include "CollisionModule/CollisionComponent.hpp"

class PhysicsModule {
public:
	int registerObject(const CollisionComponent* physicsObject);
	void unRegisterObject(int id);

	//casts a ray and returns closest intersected object and its point of intersection
	const CollisionComponent* rayCast(const sf::Vector2f& origin,
									const sf::Vector2f& direction,
									float maxDistance,
									sf::Vector2f& endPoint);

	// Checks if ray intersects with rectangle
	bool rayIntersectsRectangle(const CollisionRectangle& rectangle,
							const sf::Vector2f& origin,
							const sf::Vector2f& direction,
							float maxDistance, 
							sf::Vector2f& endPoint);

private:
	static int ID;
	std::unordered_map<int,const CollisionComponent*> physicsObjects;
};