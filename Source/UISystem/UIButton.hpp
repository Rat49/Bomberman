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

	// Returns the current text of the button
	std::string getText() const;

	// Override the draw method to render the button
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	// SFML objects to represent the button's background and text
	sf::RectangleShape buttonBackground;
	sf::Text buttonText;

	// Additional states to handle button interaction (hovered and pressed)
	bool isHovered = false;
	bool isPressed = false;

	// Flag indicating if the button is interactable
	bool isInteractable = true;
};
