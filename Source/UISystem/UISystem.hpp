#pragma once

#include <SFML/Graphics.hpp>

class UISystem
{
public:
	UISystem();

	// Updates the viewport size to handle dynamic resizing
	void setViewportSize(float width, float height);

	// Sets the UI resolution
	void setUIResolution(float width, float height);

	// Converts UI World coordinates to Viewport coordinates
	sf::Vector2f screenToViewport(const sf::Vector2f& uiWorldPos) const;

	// Converts Viewport coordinates to UI World coordinates
	sf::Vector2f viewportToScreen(const sf::Vector2f& viewportPos) const;

	// Renders the UI elements onto the given window
	void render(sf::RenderWindow& window);

private:
	// VARIABLES
	// Current dimensions of the viewport
	float viewportWidth;
	float viewportHeight;
	// Store the scale factor
	float scale;

	// Fixed UI World resolution for scaling
	sf::Vector2f uiResolution;

	// Black bars for centering UI
	sf::RectangleShape blackBars;

	//METHODS
	// Calculates the scale factor for conversion between Viewport and UI World coordinates
	float calculateScaleFactor() const;

	// Adjusts viewport settings for centering and fitting UI elements
	void updateViewportSettings();
};
