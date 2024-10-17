#pragma once

#include <SFML/Graphics.hpp>

class CollisionRectangle {
public:
	CollisionRectangle();
	// Constructor that initializes the rectangle shape
	CollisionRectangle(const sf::Vector2f& position, const sf::Vector2f& size);

	// Function to check if this rectangle overlaps with another
	bool isOverlapping(const CollisionRectangle& other) const;

	// Getter for the rectangle
	const sf::RectangleShape& getRectangle() const;

	// setting a fill color of a rectangle
	void setColor(const sf::Color& color);
private:
	sf::RectangleShape rectangle;
	bool isOverlapped;

};