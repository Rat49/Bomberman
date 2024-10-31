#pragma once

#include <SFML/Graphics.hpp>

class CollisionRectangle;
class RayCast {
public:

	RayCast() {};
	RayCast(const sf::Vector2f& origin, const sf::Vector2f& direction, const float& maxDistance) :
		rayOrigin(origin), 
		rayDirection(direction),
		rayMaxDistance(maxDistance){}

	~RayCast() {};
	// Getter for the origin
	const sf::Vector2f& getOrigin() const { return rayOrigin; }

	// Setter for origin
	void setOrigin(const sf::Vector2f& origin) { this->rayOrigin = origin; }

	// Getter for the direction
	const sf::Vector2f& getDirection() const { return rayDirection; }

	// Setter for direction
	void setDirection(const sf::Vector2f& direction) { this->rayDirection = direction; }

	// Getter for the maxDistance
	const float& getMaxDistance() const { return rayMaxDistance; }

	// Setter for maxDistance
	void setMaxDistance(const float& maxDistance) { this->rayMaxDistance = maxDistance; }

	// Checks if ray intersects with rectangle
	bool rayIntersectsRectangle(const CollisionRectangle& rectangle, sf::Vector2f& endPoint);

private:
	sf::Vector2f rayOrigin;
	sf::Vector2f rayDirection;
	float rayMaxDistance = 0.f;
};