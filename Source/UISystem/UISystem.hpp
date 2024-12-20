#pragma once

#include <SFML/Graphics.hpp>
#include "BaseModule/BaseModule.hpp"

class UIScreen;

class UISystem : public BaseModule
{
public:

	// Updates the viewport size to handle dynamic resizing
	void setViewportSize(float width, float height);

	// Sets the UI resolution
	void setUIResolution(float width, float height);

	// Converts UI coordinates to Viewport coordinates
	sf::Vector2f uiScreenToViewport(const sf::Vector2f& uiWorldPos) const;

	// Converts Viewport coordinates to UI coordinates
	sf::Vector2f viewportToUIScreen(const sf::Vector2f& viewportPos) const;

	void terminate() override;

	// Handling mouse events
	void handleMouseEvent(const sf::Event& event);

	// Adjusts viewport settings for centering and fitting UI elements
	void updateViewportSettings();

	sf::Vector2f getScale() const { return scale; }

private:
	sf::Vector2f viewportSize;
	sf::Vector2f uiResolution;
	sf::Vector2f scale;
};
