#include "UISystem/UILabel.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

// Constructor: initializes the UILabel with text, font, and character size
UILabel::UILabel(const std::string& text, const sf::Font& font, unsigned int size)
{
	labelText.setFont(font);
	labelText.setString(text);
	labelText.setCharacterSize(size);
}

// Render the label on the screen
void UILabel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Check visibility before drawing
	if (isVisible())
	{
		target.draw(labelText, states);
	}
}

// Set method to change the displayed text
void UILabel::setText(const std::string& text)
{
	labelText.setString(text);
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
}

// Returns the current text
std::string UILabel::getText() const
{
	return labelText.getString();
}
