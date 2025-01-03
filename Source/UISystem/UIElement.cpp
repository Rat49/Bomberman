#include "UISystem/UIElement.hpp"

void UIElement::setPosition(const sf::Vector2f& pos)
{
    position = pos;
}

void UIElement::setSize(const sf::Vector2f& newSize)
{
    elementSize = newSize;
}

void UIElement::setVisible(bool visibility)
{
    visible = visibility;
}

void UIElement::handleResize(const sf::Vector2f& scale)
{
    position    = sf::Vector2f(position.x * scale.x, position.y * scale.y);
    elementSize = sf::Vector2f(elementSize.x * scale.x, elementSize.y * scale.y);
}

bool UIElement::containsPoint(const sf::Vector2f& point) const
{
    return point.x >= position.x && point.x <= (position.x + elementSize.x) && point.y >= position.y &&
           point.y <= (position.y + elementSize.y);
}

void UIElement::setIsInteractable(bool interactable)
{
    isInteractable = interactable;
}
