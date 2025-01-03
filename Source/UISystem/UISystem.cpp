#include "UISystem/UISystem.hpp"
#include "UISystem/UIScreen.hpp"

// Updates the viewport size to handle dynamic resizing
void UISystem::setViewportSize(float width, float height)
{
    viewportSize.x = width;
    viewportSize.y = height;
    updateViewportSettings();
    setUIResolution(width, height);
}

// Sets the UI resolution
void UISystem::setUIResolution(float width, float height)
{
    uiResolution = sf::Vector2f(width, height);
}

// Converts UI coordinates to Viewport coordinates
sf::Vector2f UISystem::uiScreenToViewport(const sf::Vector2f& uiWorldPos) const
{
    // Apply scaling to convert UI position to viewport coordinates
    return sf::Vector2f(uiWorldPos.x * scale.x, uiWorldPos.y * scale.y);
}

// Converts Viewport coordinates to UI coordinates
sf::Vector2f UISystem::viewportToUIScreen(const sf::Vector2f& viewportPos) const
{
    // Reverse scale to retrieve the original UI coordinates
    return sf::Vector2f(viewportPos.x / scale.x, viewportPos.y / scale.y);
}

void UISystem::terminate()
{
}

// Adjusts viewport settings for centering and fitting UI elements
void UISystem::updateViewportSettings()
{
    // Calculate scale factors based on viewport and UI resolution for both axes
    scale.x = viewportSize.x / uiResolution.x;
    scale.y = viewportSize.y / uiResolution.y;
}
