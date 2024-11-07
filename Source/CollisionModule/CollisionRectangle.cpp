#include "CollisionRectangle.hpp"
#include "Common/Modules.hpp"
#include "EventSystem/EventSystem.hpp"
#include "Common/Logs.hpp"

// Constructor that sets up the rectangle shape with a position and size
CollisionRectangle::CollisionRectangle(const sf::Vector2f& position, const sf::Vector2f& size) {
	rectangle.setPosition(position);
	rectangle.setSize(size);
}

// Function to check for overlap with another Collision object
const bool CollisionRectangle::isOverlapping(CollisionRectangle& other) {
	return rectangle.getGlobalBounds().intersects(other.getRectangle().getGlobalBounds());
}

// Getter function for the internal rectangle shape
const sf::RectangleShape& CollisionRectangle::getRectangle() const {
	return rectangle;
}

// Setter for Rectangle Properties
void CollisionRectangle::setRectangleProperties(const sf::Vector2f& position, const sf::Vector2f& size) {
	rectangle.setPosition(position);
	rectangle.setSize(size);
}

// setting a fill color of a rectangle
void CollisionRectangle::setColor(const sf::Color& color) {
	rectangle.setFillColor(color);
}

//updates overlap status and calls handlers if needed
void CollisionRectangle::update(CollisionRectangle& other) {
	bool isCurrentlyOverlapping = isOverlapping(other);
	if (isCurrentlyOverlapping && !getIsOverlapped()) {
		setIsOverlapped(true);
		BeginOverlapHandler(&other);  // Trigger BeginOverlap handler
	}
	else if (!isCurrentlyOverlapping && getIsOverlapped()) {
		setIsOverlapped(false);
		EndOverlapHandler(&other);    // Trigger EndOverlap handler
	}
}

// Returns a center of rectangle
sf::Vector2f CollisionRectangle::getCenter() {
	sf::Vector2f center = rectangle.getPosition();
	center.x += rectangle.getSize().x/2;
	center.y += rectangle.getSize().y/2;
	return center;
}