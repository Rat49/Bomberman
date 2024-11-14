#pragma once

#include "UISystem/UIElement.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string>

class UIButton : public UIElement
{
public:
	UIButton(const std::string& text, const sf::Font& font, unsigned int characterSize);

	// Override event handler for the button (mouse hover and click events)
	bool handleEvent(const sf::Event& event) override;

	// Set methods for customizing the button
	void setText(const std::string& text);
	void setFont(const sf::Font& font);
	void setCharacterSize(unsigned int characterSize);
	void setSize(const sf::Vector2f& btnSize);

	void setPosition(const sf::Vector2f& pos) override;

	void setSizeFromText();

	// Set different colors for different states of the button
	void setDefaultColor(const sf::Color& color);
	void setHoverColor(const sf::Color& color);
	void setPressedColor(const sf::Color& color);

	// Returns the current text of the button
	std::string getText() const;

	sf::Vector2f UIButton::getSize() const { return buttonBackground.getSize(); }

	// Override the draw method to render the button
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// SFML objects to represent the button's background and text
	sf::RectangleShape buttonBackground;

	void resizeCharacterSize(float newCharacterSize);

private:
	sf::Text buttonText;

	// Additional states to handle button interaction (hovered and pressed)
	bool isHovered = false;
	bool isPressed = false;

	// Flag indicating if the button is interactable
	bool isInteractable = true;

	// Colors for different button states
	sf::Color defaultColor = sf::Color::Green;
	sf::Color hoverColor = sf::Color::Cyan;
	sf::Color pressedColor = sf::Color::Blue;

	unsigned int currentCharacterSize;
};
