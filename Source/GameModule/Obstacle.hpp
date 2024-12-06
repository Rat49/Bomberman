#pragma once

#include "CollisionModule/CollisionComponent.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

enum class ObstacleType
{
	Unbreakable,
	Breakable
};

class Obstacle : public sf::Sprite
{
public:
	Obstacle();

	Obstacle(ObstacleType type, sf::Vector2i position, bool hasKeyOrGate = false);

	sf::Vector2i getPosition() const;

	ObstacleType getType() const;

	bool hasKeyOrGate() const;

	void setHasKeyOrGate(bool value);

	static bool isValidUnbreakablePosition(const sf::Vector2i& position);

	CollisionComponent& getCollisionBox() const { return *collisionBox; }

private:
	ObstacleType obstacleType;
	sf::Vector2i obstaclePosition;
	std::unique_ptr<CollisionComponent> collisionBox;

	// True if there is a key or gate under the obstacle
	bool obstacleHasKeyOrGate;
};
