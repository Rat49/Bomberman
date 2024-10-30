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
	// Draw each UI element on the given target
	for (const auto& element : elements)
	{
		element->draw(target);
	}
}
