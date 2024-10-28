#pragma once

#include <SFML/Graphics.hpp>

class UISystem
{
public:
	// Constructor: initializes the UISystem with viewport dimensions
	UISystem(float viewportWidth, float viewportHeight);

	// Updates the viewport size to handle dynamic resizing
	void setViewportSize(float width, float height);

	// Converts UI World coordinates to Viewport coordinates
	sf::Vector2f toViewportCoordinates(const sf::Vector2f& uiWorldPos) const;

	// Converts Viewport coordinates to UI World coordinates
	sf::Vector2f toUIWorldCoordinates(const sf::Vector2f& viewportPos) const;

	// Renders the UI elements onto the given window
	void render(sf::RenderWindow& window);

private:
	// VARIABLES
	// Current dimensions of the viewport
	float viewportWidth, viewportHeight;

	// Fixed UI World resolution for scaling
	const sf::Vector2f uiResolution = { 1280.f, 720.f };

	// Black bars for centering UI
	sf::RectangleShape blackBars;

	//METHODS
	// Calculates the scale factor for conversion between Viewport and UI World coordinates
	float calculateScaleFactor() const;

	// Adjusts viewport settings for centering and fitting UI elements
	void updateViewportSettings();
};
