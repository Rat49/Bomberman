#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

// Base abstract class for all UI elements
// Coordinates are resolution-independent, referring to the top-left corner of each UI element.
// Operates within a virtual range (e.g., 800x600), or normalized [0,1] coordinates to enable flexibility across resolutions.
class UIElement : public sf::RenderTarget
{
public:
	virtual ~UIElement() = default;

	// A draw method that must be implemented in derived classes
	virtual void draw(sf::RenderTarget& target) const = 0;

	// Set/get methods for position
	virtual void setPosition(const sf::Vector2f& pos) = 0;
	virtual sf::Vector2f getPosition() const = 0;

	// Set/get methods for size
	virtual void setSize(const sf::Vector2f& size) = 0;
	virtual sf::Vector2f getElementSize() const = 0;

protected:
	// Position of the UI element
	sf::Vector2f position;

	// Size of the UI element
	sf::Vector2f size;
};
