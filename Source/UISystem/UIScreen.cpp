#include "UISystem/UIScreen.hpp"
#include "UISystem/UISystem.hpp"
#include "UISystem/UIButton.hpp"
#include "Common/Logs.hpp"


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

bool UIScreen::handleEvent(const sf::Event& event)
{
	// If no window is set, exit the method
	if (!window)
	{
		return false;
	}

	if (event.type == sf::Event::Resized)
	{
		view.setSize(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y));

		LOG("!!!!!!!!!! View size: width=" + std::to_string(view.getSize().x) + ", height=" + std::to_string(view.getSize().y));

		updateUIElementPositions();
	}

	// A variable to track whether the event has been processed
	bool eventHandled = false;

	for (const auto& element : elements)
	{
		// Check if the element is visible and interactive
		if (element->isVisible() && element->getIsInteractable())
		{
			// Convert mouse coordinates to virtual coordinates
			sf::Vector2f virtualPos = window->mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }, view);

			// Check if the virtual coordinates are within the element
			if (element->containsPoint(virtualPos))
			{
				//if (event.type == sf::Event::MouseButtonPressed)
				//{
					// Pass the event to the element and save the result
					eventHandled = element->handleEvent(event);
				//}
				//else if (event.type == sf::Event::MouseButtonReleased)
				//{
				//	eventHandled = element->handleEvent(event);
				//}
				//else if (event.type == sf::Event::MouseMoved)
				//{
				//	eventHandled = element->handleEvent(event);
				//}

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

void UIScreen::updateUIElementPositions()
{
	const auto scale = Modules::UI->getScale();
	for (auto& element : elements)
	{
		element->handleResize(scale);
	}
}

// Definition of a static folder to store fonts
std::unordered_map<std::string, sf::Font> UIScreen::fonts;

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
