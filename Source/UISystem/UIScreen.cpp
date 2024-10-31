#include "UISystem/UIScreen.hpp"

// Add a UI element
void UIScreen::addElement(std::shared_ptr<UIElement> element)
{
	elements.push_back(element);
}

// Remove a UI element
void UIScreen::removeElement(const std::shared_ptr<UIElement>& element)
{
	// Find the element
	auto it = std::remove(elements.begin(), elements.end(), element);

	// Erase it from the vector
	elements.erase(it, elements.end());
}

// Draw all UI elements on the given target
void UIScreen::draw(sf::RenderTarget& target)
{
	// Check if a custom view is set and apply it
	if (viewSet)
	{
		target.setView(view);  // Set the custom view if available
	}

	// Draw each UI element on the given target
	for (const auto& element : elements)
	{
		element->draw(target);
	}

	// Restore the default view if a custom view was set
	if (viewSet)
	{
		target.setView(target.getDefaultView());
	}
}

// Set the view for the UI screen
void UIScreen::setView(const sf::View& newView)
{
	view = newView;
	viewSet = true;  // Mark that a custom view has been set
}

// Clear all UI elements from the screen
void UIScreen::clearElements()
{
	elements.clear();
}
