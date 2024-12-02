#pragma once

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
	Obstacle(ObstacleType type, sf::Vector2i position, bool hasKeyOrGate = false);

	sf::Vector2i getPosition() const;

	ObstacleType getType() const;

	bool hasKeyOrGate() const;

	void setHasKeyOrGate(bool value);

	static bool isValidUnbreakablePosition(const sf::Vector2i& position);

private:
	ObstacleType obstacleType;
	sf::Vector2i obstaclePosition;

	// True if there is a key or gate under the obstacle
	bool obstacleHasKeyOrGate;
};
