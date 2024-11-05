#include "UISystem/UIScreen.hpp"

// Add a UI element
void UIScreen::addElement(const std::shared_ptr<UIElement> element)
{
	// Check for null pointer
	if (element)
	{
		elements.push_back(element);
	}
}

// Remove a UI element
void UIScreen::removeElement(const std::shared_ptr<UIElement>& element)
{
	// Check for null pointer
	if (element)
	{
		// Find the element
		auto it = std::remove(elements.begin(), elements.end(), element);

		if (it != elements.end())
		{
			// Erase it from the vector
			elements.erase(it, elements.end());
		}
	}
}

// Draw all UI elements on the given target
void UIScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Check if a custom view is set and apply it
	if (viewSet)
	{
		target.setView(view);  // Set the custom view if available
	}

	// Draw each UI element on the given target
	for (const auto& element : elements)
	{
		// Check if the element is visible before drawing
		if (element->isVisible())
		{
			target.draw(*element, states);
		}
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

	// Mark that a custom view has been set
	viewSet = true;
}

// Clear all UI elements from the screen
void UIScreen::clearElements()
{
	elements.clear();
}

void UIScreen::handleEvent(const sf::Event& event)
{
	// If no window is set, exit the method
	if (!window)
	{
		return;
	}

	for (const auto& element : elements) 
	{
		if (element->isVisible())
		{
			// Convert mouse coordinates to virtual coordinates
			sf::Vector2f virtualPos = window->mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }, view);

			// Check if the virtual coordinates are within the element
			if (element->containsPoint(virtualPos))
			{
				// Forwards the event to the first element on top of and stops further event forwarding
				element->handleEvent(event);
				break;
			}
		}
	}
}
