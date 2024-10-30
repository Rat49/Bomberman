#pragma once

#include "UISystem/UIElement.hpp"
#include <vector>
#include <memory>

class UIScreen
{
public:
	// Add a UI element
	void addElement(std::shared_ptr<UIElement> element);

	// Remove a UI element
	void removeElement(const std::shared_ptr<UIElement>& element);

	// Draw all UI elements on the given target
	void draw(sf::RenderTarget& target);

private:
	// Vector to store UI elements
	std::vector<std::shared_ptr<UIElement>> elements;
};
