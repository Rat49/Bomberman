#include "CollisionRectangle.hpp"

CollisionRectangle::CollisionRectangle() {

}
// Constructor that sets up the rectangle shape with a position and size
CollisionRectangle::CollisionRectangle(const sf::Vector2f& position, const sf::Vector2f& size) {
	rectangle.setPosition(position);
	rectangle.setSize(size);
}

// Function to check for overlap with another Collision object
bool CollisionRectangle::isOverlapping(const CollisionRectangle& other) const {
	// Get global bounds (the bounding box of the rectangle) for both objects
	return rectangle.getGlobalBounds().intersects(other.getRectangle().getGlobalBounds());
}

// Getter function for the internal rectangle shape
const sf::RectangleShape& CollisionRectangle::getRectangle() const {
	return rectangle;
}

// setting a fill color of a rectangle
void CollisionRectangle::setColor(const sf::Color& color) {
	rectangle.setFillColor(color);
}