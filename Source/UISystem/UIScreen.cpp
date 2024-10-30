#include "UISystem/UIScreen.hpp"

// Add a UI element
void UIScreen::addElement(std::shared_ptr<UIElement> element)
{
	elements.push_back(element);
}

// Remove a UI element
void UIScreen::removeElement(const std::shared_ptr<UIElement>& element)
{
	elements.remove(element);
}

// Draw all UI elements on the given target
void UIScreen::draw(sf::RenderTarget& target)
{
	// Check for elements before drawing
	if (elements.empty())
	{
		return;
	}

	// Draw each UI element on the given target
	for (const auto& element : elements)
	{
		element->draw(target);
	}
}
