#include "UISystem/UILabel.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

// Constructor: initializes the UILabel with text, font, and character size
UILabel::UILabel(const std::string& text, const sf::Font& font, unsigned int size)
{
	labelText.setFont(font);
	labelText.setString(text);
	labelText.setCharacterSize(size);

	shadowText.setFont(font);
	shadowText.setString(text);
	shadowText.setCharacterSize(size);

	setIsInteractable(false);
}

void UILabel::dropShadows(const sf::Color& labelColor, const sf::Color& shadowColor)
{
	labelText.setFillColor(labelColor);
	shadowText.setFillColor(shadowColor);

	hasShadow = true;
}

// Render the label on the screen
void UILabel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Check visibility before drawing
	if (isVisible())
	{
		if (hasShadow)
		{
			target.draw(shadowText, states);
		}
		target.draw(labelText, states);
	}
}

void UILabel::setPosition(const sf::Vector2f& pos)
{
	UIElement::setPosition(pos);

	labelText.setPosition(pos);

	float offset = (shadowText.getCharacterSize() + 0.f) / 10;
	shadowText.setPosition(sf::Vector2f(pos.x + offset, pos.y + offset));
}

// Set method to change the displayed text
void UILabel::setText(const std::string& text)
{
	labelText.setString(text);
	shadowText.setString(text);
}

// Set method to change the font of the label
void UILabel::setFont(const sf::Font& font)
{
	labelText.setFont(font);
}

// Set method to change the character size of the label
void UILabel::setCharacterSize(unsigned int newSize)
{
	labelText.setCharacterSize(newSize);
	shadowText.setCharacterSize(newSize);
}

// Returns the current text
std::string UILabel::getText() const
{
	return labelText.getString();
}

// Override handleEvent from UIElement
bool UILabel::handleEvent(const sf::Event& event)
{
	if (!getIsInteractable())
	{
		return false;
	}

	// This code will not be executed further if the element is not interactable
	if (event.type == sf::Event::MouseMoved)
	{
		float mouseX = static_cast<float>(event.mouseMove.x);
		float mouseY = static_cast<float>(event.mouseMove.y);

		isHovered = containsPoint(sf::Vector2f(mouseX, mouseY));
		if (isHovered && onHover)
		{
			// Call onHover if mouse is over the label
			onHover();
		}
	}
	// Returns false to allow other elements to process the event
	return false;
}

void UILabel::handleResize(const sf::Vector2f& scale)
{
	setCharacterSize(static_cast<unsigned int>(labelText.getCharacterSize() * scale.x));

	setSize(sf::Vector2f((getSize().x) * scale.x, (getSize().y) * scale.y));

	setPosition(sf::Vector2f((getPosition().x) * scale.x, (getPosition().y) * scale.y));
}

