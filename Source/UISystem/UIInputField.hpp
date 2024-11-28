#pragma once

#include "UISystem/UIElement.hpp"
#include "SFML/Graphics.hpp"


class UIInputField : public UIElement
{
public:

	//constructor to initialize the input field
	UIInputField(const sf::Font& font, uint32_t characterSize, const sf::Vector2f& fieldSize);

	//event handler from UIElement to handle user input
	bool handleEvent(const sf::Event& event) override;

	//draw method to render the input field
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	//set the position of the input field
	void setPosition(const sf::Vector2f& position) override;

	//set the font of the text in the input field
	void setFont(const sf::Font& font);
	
	//set the size of the input field
	void setSize(const sf::Vector2f& inputFieldSize);

	//set color for field and text
	void setColor(const sf::Color& fieldColor, const sf::Color& inputTextColor);

	//set max characters allowed to input
	void setMaxCharacters(uint32_t maxChar);

	//set new size of characters
	void setCharactersSize(uint32_t charSize);
	
	//get the current text displayed in the input field
	std::string getText() const { return m_inputText.getString(); }

private:

	//method to allow cursor to follow text 
	void cursorMovement();

	//method to manage bounds of field
	bool isFieldEnd();

private:

	//background rectangle for the input field
	sf::RectangleShape m_fieldBackground;

	//cursor for input field
	sf::RectangleShape m_cursor;

	//text displayed within the input field
	sf::Text m_inputText;

	//buffer to store the entered text
	std::string m_textBuffer;

	//max number of characters allowed
	uint32_t m_maxCharacters;

	//original size of characters
	uint32_t m_characterSizeOriginal;
	
	//flag to indicate if the field is writable
	bool m_isWriteable;

	//flag for initial text
	bool m_hasPlaceholder;

};

