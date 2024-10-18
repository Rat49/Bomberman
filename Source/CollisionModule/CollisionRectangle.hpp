#pragma once

#include <SFML/Graphics.hpp>

class CollisionRectangle {
public:
	CollisionRectangle();
	// Constructor that initializes the rectangle shape
	CollisionRectangle(const sf::Vector2f& position, const sf::Vector2f& size, int32_t IDBegin, int32_t IDEnd);

	~CollisionRectangle();
	// Function to check if this rectangle overlaps with another
	void isOverlapping(CollisionRectangle& other) ;

	//event handlers
	void BeginOverlapHandler(void* other);

	void EndOverlapHandler(void* other);

	// Getter for the rectangle
	sf::RectangleShape& getRectangle();

	// Getter for overlapping
	const bool getIsOverlapped() const { return isOverlapped; }

	// setting a fill color of a rectangle
	void setColor(const sf::Color& color);
private:
	sf::RectangleShape rectangle;
	bool isOverlapped = false;

	int32_t IDBeginOverlap;
	int32_t IDEndOverlap;

	int32_t HandleBeginOverlap;
	int32_t HandleEndOverlap;

};