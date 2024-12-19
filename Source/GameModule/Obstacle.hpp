#pragma once

#include "CollisionModule/CollisionComponent.hpp"
#include "SpriteModule/SpriteModule.hpp"
#include "CollisionModule/CollisionRectangle.hpp"
#include "SpriteModule/Animation.hpp"
#include "CollisionModule/CollisionObject.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "CollisionModule/CollisionComponent.hpp"

enum class ObstacleType
{
	Unbreakable,
	Breakable
};

class Obstacle : public sf::Sprite, public CollisionObject
{
public:
	Obstacle(ObstacleType type, sf::Vector2f position, bool hasKeyOrGate = false);

	virtual ~Obstacle() = default;

	sf::Vector2f getPosition() const;

	ObstacleType getType() const;

	bool hasKeyOrGate() const;

	void setHasKeyOrGate(bool value);

	void changeAnim(sf::Vector2f obsPos);

	static bool isValidUnbreakablePosition(const sf::Vector2f& position);

	std::shared_ptr<Animation> getCurrentAnimation() const;

	CollisionComponent& getCollisionBox() const { return *collisionBox; }

	CollisionRectangle& getCollision() { return collision; }

	bool isExploded;

private:
	ObstacleType obstacleType;
	sf::Vector2f obstaclePosition;

	int32_t currentAnimation = -1;
	int32_t idleBreakableObstacleAnimID;
	int32_t obstacleDestructionAnimID;

	CollisionRectangle collision;

	// True if there is a key or gate under the obstacle
	bool obstacleHasKeyOrGate;
    std::unique_ptr<CollisionComponent> collisionBox;

};
