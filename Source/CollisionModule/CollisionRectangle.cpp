#include "CollisionRectangle.hpp"
#include "Common/Modules.hpp"
#include "EventSystem/EventSystem.hpp"
#include "Common/Logs.hpp"

CollisionRectangle::CollisionRectangle() {

}
// Constructor that sets up the rectangle shape with a position and size
CollisionRectangle::CollisionRectangle(const sf::Vector2f& position, const sf::Vector2f& size, int32_t IDBegin, int32_t IDEnd) {
	rectangle.setPosition(position);
	rectangle.setSize(size);
	IDBeginOverlap = IDBegin;
	IDEndOverlap = IDEnd;

	HandleBeginOverlap = Modules::Events->subscribe(IDBeginOverlap,
		std::bind(&CollisionRectangle::BeginOverlapHandler, this, std::placeholders::_1));
	HandleEndOverlap = Modules::Events->subscribe(IDEndOverlap,
		std::bind(&CollisionRectangle::EndOverlapHandler, this, std::placeholders::_1));
}

CollisionRectangle::~CollisionRectangle(){
	Modules::Events->unsubscribe(IDBeginOverlap, HandleBeginOverlap);
	Modules::Events->unsubscribe(IDEndOverlap, HandleEndOverlap);
}

// Function to check for overlap with another Collision object
void CollisionRectangle::isOverlapping(CollisionRectangle& other) {
	bool isCurrentlyOverlapping = rectangle.getGlobalBounds().intersects(other.getRectangle().getGlobalBounds());

	if (isCurrentlyOverlapping && !isOverlapped) {
		isOverlapped = true;
		Modules::Events->emit(IDBeginOverlap, &other);  // Trigger BeginOverlap event
	}
	else if (!isCurrentlyOverlapping && isOverlapped) {
		isOverlapped = false;
		Modules::Events->emit(IDEndOverlap , &other);    // Trigger EndOverlap event
	}

}

//event handlers
void CollisionRectangle::BeginOverlapHandler(void* ) {
	LOG("Begin Overlap");
}

void CollisionRectangle::EndOverlapHandler(void* ) {
	LOG("End Overlap");
}

// Getter function for the internal rectangle shape
sf::RectangleShape& CollisionRectangle::getRectangle() {
	return rectangle;
}

// setting a fill color of a rectangle
void CollisionRectangle::setColor(const sf::Color& color) {
	rectangle.setFillColor(color);
}