#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

// Base abstract class for all UI elements
// Coordinates are resolution-independent, referring to the top-left corner of each UI element.
// Operates within a virtual range (e.g., 800x600), or normalized [0,1] coordinates to enable flexibility across resolutions.
class UIElement : public sf::Drawable
{
public:
	virtual ~UIElement() = default;

	// Set and get methods for position
	void setPosition(const sf::Vector2f& pos) { position = pos; }
	sf::Vector2f getPosition() const { return position; }

	// Set and get methods for dimensions
	void setSize(const sf::Vector2f& newSize) { size = newSize; }
	sf::Vector2f getSize() const { return size; }

	// Set and get methods for visibility
	void setVisible(bool visibility) { visible = visibility; }
	bool isVisible() const { return visible; }

protected:
	// Override the pure virtual draw method from sf::Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

	// Position of the UI element
	sf::Vector2f position;

	// Dimensions of the UI element
	sf::Vector2f size;

	// Visibility of UI element
	bool visible = true;
};
