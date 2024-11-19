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

	// Set method to change the displayed text
	virtual void setText(const std::string& text);

	// Set method to change the font of the label
	void setFont(const sf::Font& font);

	// Set method to change the character size of the label
	void setCharacterSize(unsigned int size);

	void setPosition(const sf::Vector2f& pos) override;

	// Returns the current text
	std::string getText() const;

	// Override the handleEvent from UIElement
	bool handleEvent(const sf::Event& event) override;

	// Functions for event registration
	std::function<void()> onHover;

	void dropShadows(const sf::Color& labelColor, const sf::Color& shadowColor);

	void removeShadow() { hasShadow = false; }

protected:
	// Render the label on the screen
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	// SFML text object to hold and display the label's text
	sf::Text labelText;

	// Same as labelText, just placed beneath it
	sf::Text shadowText;

	// If shadowText should be shown
	bool hasShadow = false;

	// Additional states to handle button interaction (hovered and pressed)
	bool isHovered = false;
};
