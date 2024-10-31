#pragma once

#include "UISystem/UIElement.hpp"
#include <SFML/Graphics/Text.hpp>
#include <string>

namespace sf
{
	class Font;
}

// Derived class that implements a simple text display element
class UILabel : public UIElement
{
public:
	// Constructor: initializes the UILabel with text, font, and character size
	UILabel(const std::string& text, const sf::Font& font, unsigned int characterSize);

	// Render the label on the screen
	void draw(sf::RenderTarget& target) const override;

	// Set method to change the displayed text
	void setText(const std::string& text);

	// Returns the current text
	std::string getText() const;

	// Sets the position of the label
	void setPosition(const sf::Vector2f& pos) override;

	sf::Vector2f getPosition() const override;

	// Set method to change the font of the label
	void setFont(const sf::Font& font);

	// Set method to change the character size of the label
	void setCharacterSize(unsigned int size);

private:
	// SFML text object to hold and display the label's text
	sf::Text labelText;
};
