#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>
#include "Common/Logs.hpp"

// Base abstract class for all UI elements
// Coordinates are resolution-independent, referring to the top-left corner of each UI element.
// Operates within a virtual range (e.g., 800x600), or normalized [0,1] coordinates to enable flexibility across resolutions.
class UIElement : public sf::Drawable
{
public:
	UIElement() : isInteractable(true) {}

	virtual ~UIElement() = default;

	// Set and get methods for position
	virtual void setPosition(const sf::Vector2f& pos) { position = pos; }
	sf::Vector2f getPosition() const { return position; }

	// Set and get methods for dimensions
	void setSize(const sf::Vector2f& newSize) { elementSize = newSize; }

	sf::Vector2f getSize() const { return elementSize; }

	// Set and get methods for visibility
	void setVisible(bool visibility) { visible = visibility; }
	bool isVisible() const { return visible; }

	// Functions for event registration
	std::function<void()> onHover;
	std::function<void()> onClick;

	// Function for event management
	virtual bool handleEvent(const sf::Event& event) = 0;

	// Checks if the coordinates are within the bounds of the element
	bool containsPoint(const sf::Vector2f& point) const
	{
		LOG("Checking containsPoint. Point: (" + std::to_string(point.x) + ", " + std::to_string(point.y) + ")");
		LOG("Button position: (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ")");
		LOG("Button size: (" + std::to_string(elementSize.x) + ", " + std::to_string(elementSize.y) + ")");

		if (elementSize.x == 0.f || elementSize.y == 0.f)
		{
			LOG("Warning: element size is zero!");
		}

		return point.x >= position.x && point.x <= position.x + elementSize.x && point.y >= position.y && point.y <= position.y + elementSize.y;
	}

	// Returns the current interactability status of the UI element
	bool getIsInteractable() const { return isInteractable; }

	// Sets the interactability status of the UI element.
	void setIsInteractable(bool interactable) { isInteractable = interactable; }

protected:
	// Override the pure virtual draw method from sf::Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

	// Position of the UI element
	sf::Vector2f position;

	// Dimensions of the UI element
	sf::Vector2f elementSize;

	// Visibility of UI element
	bool visible = true;

	// Monitoring of hover and pressed status
	bool isHovered = false;
	bool isPressed = false;

	// Flag indicating whether the UI element can respond to user interactions
	bool isInteractable;
};
