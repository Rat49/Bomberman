#include "UISystem/UIButton.hpp"
#include "Common/Logs.hpp"

UIButton::UIButton(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& buttonSize)
{
	// Set the text and font
	buttonText.setString(text);
	buttonText.setFont(font);
	buttonText.setCharacterSize(characterSize);

	shadowText.setFont(font);
	shadowText.setString(text);
	shadowText.setCharacterSize(characterSize);

	setIsInteractable(true);

	setSize(buttonSize);
}

bool UIButton::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		float mouseX = static_cast<float>(event.mouseButton.x);
		float mouseY = static_cast<float>(event.mouseButton.y);

		if (containsPoint(sf::Vector2f(mouseX, mouseY)))
		{
			isPressed = true;

			if(onClick)
				onClick();
		}
		else
		{
			isPressed = false;
		}
	}

	if (event.type == sf::Event::MouseMoved && !isPressed)
	{
		float mouseX = static_cast<float>(event.mouseMove.x);
		float mouseY = static_cast<float>(event.mouseMove.y);

		// Check if the mouse is over the button
		isHovered = containsPoint(sf::Vector2f(mouseX, mouseY));

		if (isHovered)
		{
			onHover();
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && isPressed)
	{
		if (onRelease) {
			onRelease();
		}
		isPressed = false;

		if (isHovered && onHover) {
			onHover();
		}
	}

	return isHovered || isPressed;
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

void UIButton::setPosition(const sf::Vector2f& pos)
{
	UIElement::setPosition(pos);

	buttonBackground.setPosition(pos);
	buttonText.setPosition(buttonBackground.getPosition().x + 10.f, buttonBackground.getPosition().y + 5.f);

	float offset = (shadowText.getCharacterSize() + 0.f) / 10;
	shadowText.setPosition(buttonText.getPosition().x + offset, buttonText.getPosition().y + offset);
}

void UIButton::setSize(const sf::Vector2f& newSize)
{
	UIElement::setSize(newSize);
	buttonBackground.setSize(newSize);
}

// Set default button color
void UIButton::setDefaultColor(const sf::Color& color)
{
	defaultColor = color;
}

// Set hovered button color
void UIButton::setHoverColor(const sf::Color& color)
{
	hoverColor = color;
}

// Set pressed button color
void UIButton::setPressedColor(const sf::Color& color)
{
	pressedColor = color;
}

// Get the button's text
std::string UIButton::getText() const
{
	return buttonText.getString();
}

// Draw the button
void UIButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Color currentColor;

	if (isPressed)
	{
		currentColor = pressedColor;
	}
	else if (isHovered)
	{
		currentColor = hoverColor;
	}
	else
	{
		currentColor = defaultColor;
	}
	
	sf::RectangleShape tempBackground = buttonBackground;
	tempBackground.setFillColor(currentColor);
	

	// Draw the background
	target.draw(tempBackground, states);

	if (hasShadow) {
		target.draw(shadowText, states);
	}

	// Draw the text
	target.draw(buttonText, states);
}

void UIButton::dropShadows(const sf::Color& labelColor, const sf::Color& shadowColor)
{
	buttonText.setFillColor(labelColor);
	shadowText.setFillColor(shadowColor);

	hasShadow = true;
}
