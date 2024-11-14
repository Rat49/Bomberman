#include "UISystem/UIButton.hpp"
#include "Common/Logs.hpp"

UIButton::UIButton(const std::string& text, const sf::Font& font, unsigned int characterSize)
{
	// Set the text and font
	buttonText.setString(text);
	buttonText.setFont(font);
	buttonText.setCharacterSize(characterSize);
	currentCharacterSize = characterSize;

	setIsInteractable(true);

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

bool UIButton::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		float mouseX = static_cast<float>(event.mouseButton.x);
		float mouseY = static_cast<float>(event.mouseButton.y);

		if (containsPoint(sf::Vector2f(mouseX, mouseY)))
		{
			isPressed = true;
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
		//LOG("Mouse moved. isHovered: " + std::string(isHovered ? "true" : "false"));

		if (isHovered && !isPressed)
		{
			LOG("Hover callback called.");
			// Call onHover callback
			onHover();
		}
	}

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		if (onClick)
		{
			LOG("Click callback called.");
			// Call onClick callback
			onClick();
		}
		//isPressed = false;
	}
	else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		isPressed = false;
		LOG("Button released.");

		float mouseX = static_cast<float>(event.mouseMove.x);
		float mouseY = static_cast<float>(event.mouseMove.y);

		// Check if the mouse is over the button
		isHovered = containsPoint(sf::Vector2f(mouseX, mouseY));
		//LOG("Mouse moved. isHovered: " + std::string(isHovered ? "true" : "false"));

		if (isHovered && !isPressed)
		{
			LOG("Hover callback called.");
			// Call onHover callback
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

void UIButton::setSizeFromText()
{
	sf::FloatRect bounds = buttonText.getLocalBounds();
	LOG("TEXT BUTTON size left: " + std::to_string(buttonText.getLocalBounds().left) +
		" , top: " + std::to_string(buttonText.getLocalBounds().top) +
		" , width: " + std::to_string(buttonText.getLocalBounds().width) +
		" , height: " + std::to_string(buttonText.getLocalBounds().height));

	buttonBackground.setSize(sf::Vector2f(bounds.width + 20.f, bounds.height + 30.f));
	elementSize = sf::Vector2f(bounds.width + 20.f, bounds.height + 10.f);

	LOG("BUTTON size x: " + std::to_string(buttonBackground.getSize().x) + " , y: " + std::to_string(buttonBackground.getSize().y));
	//LOG("ELEMENT size x: " + std::to_string(elementSize.getSize().x) + " , y: " + std::to_string(elementSize.getSize().y));
}

void UIButton::resizeCharacterSize(float newCharacterSize) 
{
	currentCharacterSize = (unsigned int)(currentCharacterSize * newCharacterSize);
	buttonText.setCharacterSize(currentCharacterSize);
}

void UIButton::setPosition(const sf::Vector2f& pos)
{
	UIElement::setPosition(pos);

	buttonBackground.setPosition(pos);
	buttonText.setPosition(buttonBackground.getPosition().x + 10.f, buttonBackground.getPosition().y + 5.f);

	sf::FloatRect hitbox = buttonBackground.getGlobalBounds();

	//setSizeFromText();
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

	// Draw the text
	target.draw(buttonText, states);
}
