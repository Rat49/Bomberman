#pragma once

#include <SFML/Graphics.hpp>

class CollisionRectangle;
class RayCast {
public:

	RayCast() {};
	RayCast(const sf::Vector2f& origin, const sf::Vector2f& direction) : rayOrigin(origin), rayDirection(direction){}

	~RayCast() {};
	// Getter for the origin
	const sf::Vector2f& getOrigin() const { return rayOrigin; }

	// Setter for origin
	void setOrigin(const sf::Vector2f& origin) { this->rayOrigin = origin; }

	// Getter for the direction
	const sf::Vector2f& getDirection() const { return rayDirection; }

	// Setter for direction
	void setDirection(const sf::Vector2f& direction) { this->rayDirection = direction; }

	// Checks if ray intersects with rectangle
	bool rayIntersectsRectangle(const CollisionRectangle& rectangle, sf::Vector2f& endPoint);

private:
	sf::Vector2f rayOrigin;
	sf::Vector2f rayDirection;
};