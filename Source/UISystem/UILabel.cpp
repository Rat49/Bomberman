#include "UISystem/UILabel.hpp"

// Constructor: initializes the UILabel with text, font, and character size
UILabel::UILabel(const std::string& text, const sf::Font& font, unsigned int size)
{
	labelText.setFont(font);
	labelText.setString(text);
	labelText.setCharacterSize(size);
}

// Render the label on the screen
void UILabel::draw(sf::RenderTarget& target)
{
	target.draw(labelText);
}

// Set method to change the displayed text
void UILabel::setText(const std::string& text)
{
	labelText.setString(text);
}

// Returns the current text
std::string UILabel::getText() const
{
	return labelText.getString();
}

// Sets the position of the label
void UILabel::setPosition(const sf::Vector2f& pos)
{
	labelText.setPosition(pos);
}
