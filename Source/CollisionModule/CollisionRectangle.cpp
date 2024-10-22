#include "CollisionRectangle.hpp"
#include "Common/Modules.hpp"
#include "EventSystem/EventSystem.hpp"
#include "Common/Logs.hpp"

CollisionRectangle::CollisionRectangle() {
	rectangle.setPosition(sf::Vector2f(100.f, 100.f));
	rectangle.setSize(sf::Vector2f(100.f, 100.f));
}
// Constructor that sets up the rectangle shape with a position and size
CollisionRectangle::CollisionRectangle(const sf::Vector2f& position, const sf::Vector2f& size) {
	rectangle.setPosition(position);
	rectangle.setSize(size);

}

// Function to check for overlap with another Collision object
const bool CollisionRectangle::isOverlapping(CollisionRectangle& other){
	return rectangle.getGlobalBounds().intersects(other.getRectangle().getGlobalBounds());
}

// Getter function for the internal rectangle shape
sf::RectangleShape& CollisionRectangle::getRectangle() {
	return rectangle;
}

// setting a fill color of a rectangle
void CollisionRectangle::setColor(const sf::Color& color) {
	rectangle.setFillColor(color);
}

