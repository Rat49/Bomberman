#include "UISystem/UISystem.hpp"

// Constructor: initializes the UISystem with viewport dimensions
UISystem::UISystem() 
{
	setViewportSize(1280.0f, 720.0f);
	updateViewportSettings();
}

// Updates the viewport size to handle dynamic resizing
void UISystem::setViewportSize(float width, float height) 
{
	viewportWidth = width;
	viewportHeight = height;
	updateViewportSettings();
	// Pre-calculate the scale here
	scale = calculateScaleFactor();
}

// Sets the UI resolution
void UISystem::setUIResolution(float width, float height)
{
	uiResolution = sf::Vector2f(width, height);
	updateViewportSettings();
}

// Calculates the scale factor for conversion between Viewport and UI World coordinates
float UISystem::calculateScaleFactor() const 
{
	// Calculate scale factors based on viewport and UI resolution for both axes
	float scaleX = viewportWidth / uiResolution.x;
	float scaleY = viewportHeight / uiResolution.y;

	// Choose the smaller scale factor to avoid stretching
	return std::min(scaleX, scaleY);
}

// Converts UI World coordinates to Viewport coordinates
sf::Vector2f UISystem::screenToViewport(const sf::Vector2f& uiWorldPos) const
{
	// Calculate offsets to center the UI in the viewport
	sf::Vector2f offset(
		(viewportWidth - uiResolution.x * scale) / 2,
		(viewportHeight - uiResolution.y * scale) / 2
	);

	// Apply scaling and offset to convert UI world position to viewport coordinates
	return sf::Vector2f(uiWorldPos.x * scale + offset.x, uiWorldPos.y * scale + offset.y);
}

// Converts Viewport coordinates to UI World coordinates
sf::Vector2f UISystem::viewportToScreen(const sf::Vector2f& viewportPos) const
{
	// Calculate offsets to reverse the centering effect in the viewport
	sf::Vector2f offset(
		(viewportWidth - uiResolution.x * scale) / 2,
		(viewportHeight - uiResolution.y * scale) / 2
	);

	// Reverse offset and scale to retrieve the original UI world coordinates
	return sf::Vector2f((viewportPos.x - offset.x) / scale, (viewportPos.y - offset.y) / scale);
}

// Adjusts viewport settings for centering and fitting UI elements
void UISystem::updateViewportSettings() 
{
	// Calculate the scaling factor to center the UI within the viewport
	scale = calculateScaleFactor();

	// Calculate offsets based on the difference between viewport dimensions and UI resolution
	// float offsetX = (viewportWidth - uiResolution.x * scale) / 2; // I don't use this anywhere for now
	float offsetY = (viewportHeight - uiResolution.y * scale) / 2;

	// Set the size for the top and bottom black bars
	blackBars.setSize(sf::Vector2f(viewportWidth, offsetY));
	// Set the fill color of the black bars to black
	blackBars.setFillColor(sf::Color::Black);
}

// Renders the UI elements onto the given window
void UISystem::render(sf::RenderWindow& window) 
{
	// Display UI elements when I have them
	
	// Just for test
	window.clear(sf::Color::Black);

}
