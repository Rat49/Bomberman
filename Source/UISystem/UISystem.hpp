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

	// Converts UI coordinates to Viewport coordinates
	sf::Vector2f uiScreenToViewport(const sf::Vector2f& uiWorldPos) const;

	// Converts Viewport coordinates to UI coordinates
	sf::Vector2f viewportToUIScreen(const sf::Vector2f& viewportPos) const;

private:
	// VARIABLES
	// Current dimensions of the viewport
	float viewportWidth;
	float viewportHeight;
	// Store the scale factor
	float scale;

	// Fixed UI World resolution for scaling
	sf::Vector2f uiResolution;

	//METHODS
	// Calculates the scale factor for conversion between Viewport and UI coordinates
	float calculateScaleFactor() const;

	// Adjusts viewport settings for centering and fitting UI elements
	void updateViewportSettings();
};
