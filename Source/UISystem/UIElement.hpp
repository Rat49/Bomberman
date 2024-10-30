#pragma once

#include <SFML/Graphics.hpp>

// Base abstract class for all UI elements
class UIElement
{
public:
	virtual ~UIElement() = default;

	// A draw method that must be implemented in derived classes
	virtual void draw(sf::RenderTarget& target) = 0;

	// Set/get methods for position
	void setPosition(const sf::Vector2f& pos);
	sf::Vector2f getPosition() const;

	// Set/get methods for size
	void setSize(const sf::Vector2f& size);
	sf::Vector2f getSize() const;

protected:
	// Position of the UI element
	sf::Vector2f position;

	// Size of the UI element
	sf::Vector2f size;
};
