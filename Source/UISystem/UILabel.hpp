#pragma once

#include "UISystem/UIElement.hpp"
#include <SFML/Graphics.hpp>
#include <string>

// Derived class that implements a simple text display element
class UILabel : public UIElement
{
public:
	// Constructor: initializes the UILabel with text, font, and character size
	UILabel(const std::string& text, const sf::Font& font, unsigned int size);

	// Render the label on the screen
	void draw(sf::RenderTarget& target) override;

	// Set method to change the displayed text
	void setText(const std::string& text);

	// Returns the current text
	std::string getText() const;

	// Sets the position of the label
	void setPosition(const sf::Vector2f& pos);

private:
	// SFML text object to hold and display the label's text
	sf::Text labelText;
};
