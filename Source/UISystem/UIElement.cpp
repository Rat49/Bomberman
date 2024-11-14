#include "UISystem/UIElement.hpp"

void UIElement::setPosition(const sf::Vector2f &pos) {
  position = pos;
}

void UIElement::setSize(const sf::Vector2f &newSize) {
  elementSize = newSize;
}

void UIElement::setVisible(bool visibility) {
  visible = visibility;
}

bool UIElement::containsPoint(const sf::Vector2f &point) const {
  return point.x >= position.x && point.x <= (position.x + elementSize.x) &&
         point.y >= position.y && point.y <= (position.y + elementSize.y);
}

void UIElement::setIsInteractable(bool interactable) {
  isInteractable = interactable;
}
