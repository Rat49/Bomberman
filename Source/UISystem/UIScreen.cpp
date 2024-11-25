#include "UISystem/UIScreen.hpp"
#include "UISystem/UISystem.hpp"
#include "UISystem/UIButton.hpp"
#include "AssetManager/AssetManager.hpp"
#include "Common/Logs.hpp"

namespace {
	const std::string BASE_PATH = "Game/Fonts/";
	const std::string FILE_EXTENSION = ".ttf";
}

// Add a UI element
void UIScreen::addElement(const std::string& elementName, const std::shared_ptr<UIElement> element)
{
	// Check for null pointer
	if (element) {
		if (elements.find(elementName) == elements.end()) {
			elements[elementName] = element;
		}
		else {
			LOG("Error: adding element to UIScreen with name that already exists");
		}
	}
	else {
		LOG("Error: adding nullptr element to UIScreen");
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
		// Set the custom view if available
		target.setView(view);
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

const sf::Font& UIScreen::getFont(const std::string& fontName)
{
	const std::string assetPath = BASE_PATH + fontName + FILE_EXTENSION;
	Modules::Assets->getFont(assetPath);

	std::shared_ptr<sf::Font> fontPtr = std::make_shared<sf::Font>();
	fontPtr = Modules::Assets->getFont(assetPath);

	if (!fontPtr)
	{
		LOG("Failed to load font from path: [$]", assetPath);
		static sf::Font emptyFont;
		return emptyFont;
	}

	return *fontPtr;
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

		updateUIElementPositions();
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

void UIScreen::updateUIElementPositions()
{
	const auto scale = Modules::UI->getScale();
	for (auto& element : elements)
	{
		element.second->handleResize(scale);
	}
}
