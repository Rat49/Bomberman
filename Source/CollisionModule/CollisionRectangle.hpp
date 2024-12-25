#pragma once

#include "CollisionModule/CollisionObject.hpp"
#include <SFML/Graphics.hpp>

class CollisionRectangle
{
public:
	CollisionRectangle() = default;
	// Constructor that initializes the rectangle shape
	CollisionRectangle(const sf::Vector2f& position, const sf::Vector2f& size);

	//updates overlap status and calls handlers if needed
	void update(CollisionRectangle&);

	//event handlers
	virtual void BeginOverlapHandler(void*) {};

	virtual void EndOverlapHandler(void*) {};

	// Getter for the rectangle
	const sf::RectangleShape& getRectangle() const;

	// Setter for Rectangle
	void setRectangle(const sf::RectangleShape& sfRectangle) { this->rectangle = sfRectangle; }

	// Getter for overlapping
	const bool getIsOverlapped() const { return isOverlapped; }

	// Setter for overlapping
	void setIsOverlapped(bool overlap) { isOverlapped = overlap; }

	// Getter for the parent
	void* getParent() const { return parentComponent; }

    CollisionObject* getObjectParent() const { return parent; }

	// Setter for the parent
    void setParent(void* nParent) {  this->parentComponent = nParent; }

	void setObjectParent(CollisionObject* newParent) { parent = newParent; }

	// Setter for Rectangle Properties
	void setRectangleProperties(const sf::Vector2f& position, const sf::Vector2f& size);

	// Setting a fill color of a rectangle
	void setColor(const sf::Color& color);

	// Returns a center of rectangle
	sf::Vector2f getCenter();

	// Function to check if this rectangle overlaps with another
	const bool isOverlapping(CollisionRectangle& other);

protected:

	//collision rectangle
	sf::RectangleShape rectangle;

	//is currently overlapping something
	bool isOverlapped = false;

	//pointer to the parent object/component
	void* parentComponent;

	CollisionObject* parent;
private:
};