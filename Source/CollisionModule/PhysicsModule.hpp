#pragma once
#include <unordered_map>
#include <memory>
#include "CollisionModule/CollisionComponent.hpp"
#include "BaseModule/BaseModule.hpp"

class PhysicsModule : public BaseModule
{
public:
    CollisionComponent* getObj(int i);

	int registerObject(CollisionComponent* physicsObject);
	void unRegisterObject(int id);

    void deleteObject(CollisionComponent* physicsObject);
    void updateCollision();

	//casts a ray and returns closest intersected object and its point of intersection
	const CollisionComponent* rayCast(const sf::Vector2f& origin,
									const sf::Vector2f& direction,
									float maxDistance,
									sf::Vector2f& endPoint);

	std::vector<std::pair<CollisionComponent*, sf::Vector2f>> rayCastAll(
		const sf::Vector2f& origin,
		const sf::Vector2f& direction,
		float maxDistance);

	// Checks if ray intersects with rectangle
	bool rayIntersectsRectangle(const CollisionRectangle& rectangle,
							const sf::Vector2f& origin,
							const sf::Vector2f& direction,
							float maxDistance, 
							sf::Vector2f& endPoint);

	void terminate() override;

	bool tryToMove();

private:
	static int ID;
	std::unordered_map<int, CollisionComponent*> physicsObjects;
};