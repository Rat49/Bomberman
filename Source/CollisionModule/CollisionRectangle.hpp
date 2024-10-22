#pragma once

#include <SFML/Graphics.hpp>

class CollisionRectangle {
public:
	CollisionRectangle();
	// Constructor that initializes the rectangle shape
	CollisionRectangle(const sf::Vector2f& position, const sf::Vector2f& size);

	//updates overlap status and emits events if needed
	virtual void update(CollisionRectangle& ) {};

	//event handlers
	virtual void BeginOverlapHandler(void* ) {};

	virtual void EndOverlapHandler(void* ) {};

	// Getter for the rectangle
	sf::RectangleShape& getRectangle();

	// Getter for overlapping
	const bool getIsOverlapped() const { return isOverlapped; }

	// Setter for overlapping
	void setIsOverlapped(bool overlap) { isOverlapped = overlap; }

	// setting a fill color of a rectangle
	void setColor(const sf::Color& color);
protected:
	// Function to check if this rectangle overlaps with another
	const bool isOverlapping(CollisionRectangle& other);

	sf::RectangleShape rectangle;
	bool isOverlapped = false;
private:

};