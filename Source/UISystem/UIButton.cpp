#include "UISystem/UIButton.hpp"

UIButton::UIButton(const std::string& text, const sf::Font& font, unsigned int characterSize)
{
	// Set the text and font
	buttonText.setString(text);
	buttonText.setFont(font);
	buttonText.setCharacterSize(characterSize);

	setIsInteractable(true);

	// Set the size of the button based on text size
	buttonBackground.setSize(sf::Vector2f(buttonText.getLocalBounds().width + 20.f, buttonText.getLocalBounds().height + 10.f));

	// Center the text inside the button
	buttonText.setPosition(buttonBackground.getPosition().x + 10.f, buttonBackground.getPosition().y + 5.f);

	// Draw the button with a background color
	if (isHovered)
	{
		// Hovered color
		buttonBackground.setFillColor(sf::Color::Cyan);
	}
	else
	{
		// Default color
		buttonBackground.setFillColor(sf::Color::Green);
	}
}

// Handle events (hover and click)
bool UIButton::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseMoved)
	{
		float mouseX = static_cast<float>(event.mouseMove.x);
		float mouseY = static_cast<float>(event.mouseMove.y);

		// Check if the mouse is over the button
		isHovered = containsPoint(sf::Vector2f(mouseX, mouseY));

		if (isHovered && onHover)
		{
			// Call onHover callback
			onHover();
		}
	}

	if (event.type == sf::Event::MouseButtonPressed && isHovered && event.mouseButton.button == sf::Mouse::Left)
	{
		isPressed = true;
		if (onClick)
		{
			// Call onClick callback
			onClick();
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased && isPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		isPressed = false;
	}

	// Return if the event was handled
	return isHovered;
}

// Set the button's text
void UIButton::setText(const std::string& text)
{
	buttonText.setString(text);
}

// Set the button's font
void UIButton::setFont(const sf::Font& font)
{
	buttonText.setFont(font);
}

// Set the character size for the text
void UIButton::setCharacterSize(unsigned int characterSize)
{
	buttonText.setCharacterSize(characterSize);
}

// Set the button's size
void UIButton::setSize(const sf::Vector2f& btnSize)
{
	buttonBackground.setSize(btnSize);
	buttonText.setPosition(buttonBackground.getPosition().x + 10.f, buttonBackground.getPosition().y + 5.f);
}

// Get the button's text
std::string UIButton::getText() const
{
	return buttonText.getString();
}

// Draw the button
void UIButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Specify the color but not change the buttonBackground directly in the const method
	sf::Color currentColor = isHovered ? sf::Color::Cyan : sf::Color::Green;

	sf::RectangleShape tempBackground = buttonBackground;
	tempBackground.setFillColor(currentColor);

	// Draw the background
	target.draw(tempBackground, states);

	// Draw the text
	target.draw(buttonText, states);
}
