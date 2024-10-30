#pragma once

#include <SFML/System/Vector2.hpp>

namespace sf
{
	class RenderTarget;
}

// Base abstract class for all UI elements
// Coordinates are resolution-independent, referring to the top-left corner of each UI element.
// Operates within a virtual range (e.g., 800x600), or normalized [0,1] coordinates to enable flexibility across resolutions.
class UIElement
{
public:
	virtual ~UIElement() = default;

	// A draw method that must be implemented in derived classes
	virtual void draw(sf::RenderTarget& target) = 0;

	// Set/get methods for position
	virtual void setPosition(const sf::Vector2f& pos);
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
