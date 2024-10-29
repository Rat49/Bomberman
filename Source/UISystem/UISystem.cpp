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

// Converts UI coordinates to Viewport coordinates
sf::Vector2f UISystem::uiScreenToViewport(const sf::Vector2f& uiWorldPos) const
{
	// Apply scaling to convert UI position to viewport coordinates
	return sf::Vector2f(uiWorldPos.x * scale, uiWorldPos.y * scale);
}

// Converts Viewport coordinates to UI coordinates
sf::Vector2f UISystem::viewportToUIScreen(const sf::Vector2f& viewportPos) const
{
	// Reverse scale to retrieve the original UI coordinates
	return sf::Vector2f(viewportPos.x / scale, viewportPos.y / scale);
}

// Adjusts viewport settings for centering and fitting UI elements
void UISystem::updateViewportSettings() 
{
	// Calculate the scaling factor to center the UI within the viewport
	scale = calculateScaleFactor();

	if (scale <= 0) 
	{
		// Set to minimum value to avoid program crash
		scale = 0.01f;
	}
}
