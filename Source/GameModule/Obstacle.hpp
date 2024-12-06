#pragma once

#include "CollisionModule/CollisionComponent.hpp"
#include "SpriteModule/SpriteModule.hpp"
#include "CollisionModule/CollisionRectangle.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

enum class ObstacleType
{
	Unbreakable,
	Breakable
};

class Obstacle : public sf::Sprite, public CollisionComponent
{
public:
	Obstacle();

	Obstacle(ObstacleType type, sf::Vector2i position, bool hasKeyOrGate = false);

	sf::Vector2i getPosition() const;

	ObstacleType getType() const;

	bool hasKeyOrGate() const;

	void setHasKeyOrGate(bool value);

	// Drawing a Obstacle
	void draw(sf::RenderWindow& window, sf::Vector2f obsPos);

	static bool isValidUnbreakablePosition(const sf::Vector2i& position);

	CollisionComponent& getCollisionBox() const { return *collisionBox; }

	std::shared_ptr<Animation> getCurrentAnimation() const;

	CollisionRectangle& getCollision() { return collision; }

private:
	ObstacleType obstacleType;
	sf::Vector2i obstaclePosition;
	std::unique_ptr<CollisionComponent> collisionBox;
	int32_t currentAnimation = -1;
	int32_t obstacleDestructionAnimID;;

	CollisionRectangle collision;

	// True if there is a key or gate under the obstacle
	bool obstacleHasKeyOrGate;
};
