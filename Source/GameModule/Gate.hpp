#pragma once

#include "CollisionModule/CollisionComponent.hpp"
#include "CollisionModule/CollisionRectangle.hpp"
#include "CollisionModule/CollisionObject.hpp"
#include "CollisionModule/PhysicsModule.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "GameModule/Key.hpp"

class Gate : public sf::Sprite, public CollisionObject
{
public:
	Gate(const sf::Vector2i& position, bool isLocked = true, std::shared_ptr<Key> key = nullptr);

	sf::Vector2i getGatePosition() const;
	bool isLocked() const;
	void unlock(std::shared_ptr<Key> key);

	CollisionComponent& getCollisionBox() const { return *collisionBox; }

    CollisionRectangle& getCollision() { return collision; }

private:
	sf::Vector2i gatePosition;
	bool locked = true;
	std::shared_ptr<Key> associatedKey;

	std::unique_ptr<CollisionComponent> collisionBox;

    CollisionRectangle collision;

    int32_t collisionBoxID;
};
