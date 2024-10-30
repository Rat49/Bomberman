#include "UISystem/UIElement.hpp"

// Set position
void UIElement::setPosition(const sf::Vector2f& pos)
{
	position = pos;
}

// Return the current position of the UI element
sf::Vector2f UIElement::getPosition() const
{
	return position;
}

// Set size
void UIElement::setSize(const sf::Vector2f& size)
{
	this->size = size;
}

// Return the current size of the UI element
sf::Vector2f UIElement::getSize() const
{
	return size;
}
