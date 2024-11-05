#pragma once

#include "UISystem/UIElement.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <vector>
#include <memory>

class UIScreen : public UIElement
{
public:
	// Add a UI element
	void addElement(const std::shared_ptr<UIElement> element);

	// Remove a UI element
	void removeElement(const std::shared_ptr<UIElement>& element);

	// Set the view for the UI screen
	void setView(const sf::View& view);

	// Clear all UI elements from the screen
	void clearElements();

	void handleEvent(const sf::Event& event) override;

	// Set the render window for event handling
	void setWindow(sf::RenderWindow* renderWindow) { window = renderWindow; }

protected:
	// Override draw method to draw all UI elements on the given target
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	// Vector to store UI elements
	std::vector<std::shared_ptr<UIElement>> elements;

	// Optional view for handling UI viewport settings
	sf::View view;

	// Pointer to the render window
	sf::RenderWindow* window = nullptr;

	// Flag to check if view is set
	bool viewSet = false;
};
