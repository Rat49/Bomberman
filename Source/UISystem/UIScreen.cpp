#include "UISystem/UIScreen.hpp"
#include "Common/Logs.hpp"

// Add a UI element
void UIScreen::addElement(const std::string& elementName, const std::shared_ptr<UIElement> element)
{
	// Check for null pointer
	if (element)
	{
		elements[elementName] = element;
	}
}

std::shared_ptr<UIElement> UIScreen::getElement(const std::string& elementName) const
{
	auto it = elements.find(elementName);
	if (it != elements.end()) {
		return it->second;
	}
	return nullptr;
}

// Remove a UI element
void UIScreen::removeElement(const std::string& element)
{
	// Find the element
	auto it = elements.find(element);
	if (it != elements.end())
	{
		elements.erase(it);
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
		if (element.second->isVisible())
		{
			target.draw(*element.second, states);
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

bool UIScreen::handleEvent(const sf::Event& event)
{
	// If no window is set, exit the method
	if (!window)
	{
		return false;
	}

	// A variable to track whether the event has been processed
	bool eventHandled = false;

	for (const auto& element : elements)
	{
		// Check if the element is visible and interactive
		if (element.second->isVisible() && element.second->getIsInteractable())
		{
			// Convert mouse coordinates to virtual coordinates
			sf::Vector2f virtualPos = window->mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }, view);

			// Check if the virtual coordinates are within the element
			if (element.second->containsPoint(virtualPos))
			{
				// Pass the event to the element and save the result
				eventHandled = element.second->handleEvent(event);

				// If the event has been processed, stop further processing
				if (eventHandled)
				{
					break;
				}

				break;
			}
		}
	}
	// Returns whether the event was processed
	return eventHandled;
}

// Definition of a static folder to store fonts
std::unordered_map<std::string, sf::Font> UIScreen::fonts;

// needs to be changed! (it also makes system to throw exception on closure, because of the way of storing fonts) 
sf::Font& UIScreen::getFont(const std::string& fontName) {
	// Checks if the font is already loaded and cached
	auto it = fonts.find(fontName);
	if (it != fonts.end())
	{
		// If found, returns the existing font
		return it->second;
	}

	// If the font is not loaded, it tries to load it
	sf::Font font;
	if (!font.loadFromFile("Assets/Fonts/" + fontName + ".ttf"))
	{
		// Logs an error if the font cannot be loaded
		LOG("Failed to load font: $" + fontName + ". Loading default font.\n");


		// Loads the default font if the requested font is not found
		if (!font.loadFromFile("Assets/Fonts/arial.ttf"))
		{
			LOG("Failed to load default font!\n");
		}
	}

	// Adds the loaded font to the folder and returns it
	fonts[fontName] = font;
	return fonts[fontName];
}
