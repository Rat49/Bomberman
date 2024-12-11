#include "UIInputField.hpp"
#include "Common/Logs.hpp"

namespace {

	const float INPUT_TEXT_OFFSET = 5.0f;
	const float CURSOR_OFFSET = 2.0f;
}


UIInputField::UIInputField(const sf::Font& font, uint32_t characterSize, const sf::Vector2f& fieldSize)
	:m_maxCharacters(30), m_hasPlaceholder(true), m_characterSizeOriginal(characterSize)
{
	//setup input field
	setSize(fieldSize);

	//setup input text
	setCharactersSize(characterSize);
	setFont(font);

	//setup color of both
	setColor(sf::Color::Black, sf::Color::White);

	m_isWriteable = false;
	setIsInteractable(true);

	//set initial text
	m_textBuffer = m_initialText;
	m_inputText.setString(m_textBuffer);
}

void UIInputField::setPosition(const sf::Vector2f& pos)
{
	UIElement::setPosition(pos);

	//positions of field and text
	m_fieldBackground.setPosition(pos);
	m_inputText.setPosition(pos.x + INPUT_TEXT_OFFSET, pos.y + (m_fieldBackground.getSize().y - m_inputText.getCharacterSize()) / 2);

	//position of cursor
	sf::FloatRect textBounds = m_inputText.getGlobalBounds();
	m_cursor.setPosition(textBounds.left + textBounds.width+ CURSOR_OFFSET, 
						 m_fieldBackground.getPosition().y + (m_fieldBackground.getSize().y - m_inputText.getCharacterSize()) / 2);
}

void UIInputField::setSize(const sf::Vector2f& fieldSize)
{
	UIElement::setSize(fieldSize);

	m_fieldBackground.setSize(fieldSize);
}

void UIInputField::setColor(const sf::Color& fieldColor, const sf::Color& inputTextColor)
{
	m_fieldBackground.setFillColor(fieldColor);
	m_inputText.setFillColor(inputTextColor);
}

void UIInputField::setMaxCharacters(uint32_t maxChar)
{
	m_maxCharacters = maxChar;
}

void UIInputField::setCharactersSize(uint32_t charSize)
{
	m_characterSizeOriginal = charSize;
	m_inputText.setCharacterSize(charSize);
}

void UIInputField::setText(const std::string& newText)
{
	m_inputText.setString(newText); 
	m_textBuffer = newText;
}

void UIInputField::setWritable(bool writable)
{
	m_isWriteable = writable;
	if(!writable)
		m_cursor.setSize(sf::Vector2f(0.f, 0.f));
}

void UIInputField::setFont(const sf::Font& font)
{
	m_inputText.setFont(font);
}

bool UIInputField::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		float mouseX = static_cast<float>(event.mouseButton.x);
		float mouseY = static_cast<float>(event.mouseButton.y);

		m_isWriteable = containsPoint(sf::Vector2f(mouseX, mouseY));


		if (m_isWriteable)
		{
			//create and display cursor (thin vertical line)
			m_cursor.setSize(sf::Vector2f(CURSOR_OFFSET, static_cast<float>(m_inputText.getCharacterSize())));
			m_cursor.setFillColor(m_inputText.getFillColor());

			//hide initial text
			if (m_hasPlaceholder)
			{
				m_textBuffer.clear();
				m_inputText.setString("");
				m_hasPlaceholder = false;
			}
		}
		else
		{
			//hide cursor
			m_cursor.setSize(sf::Vector2f(0.f, 0.f));

			//show initial text if nothing is written
			if (m_textBuffer.empty() && !m_hasPlaceholder)
			{
				m_hasPlaceholder = true;
				m_textBuffer = m_initialText;
				m_inputText.setString(m_textBuffer);
			}
		}

		//follow position with cursor
		cursorMovement();
	}

	if (m_isWriteable && event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode == '\b') //backspace (delete char)
		{
			if (!m_textBuffer.empty())
			{
				m_textBuffer.pop_back();
			}
		}
		else if (event.text.unicode >= 32 && event.text.unicode <= 126) //printable characters
		{
			if (m_textBuffer.size() <= m_maxCharacters && !isFieldEnd())
			{
				m_textBuffer += static_cast<char>(event.text.unicode);
			}
		}

		
		//fill input field text with chars
		m_inputText.setString(m_textBuffer);

		//follow position with cursor
		cursorMovement();
	}

	return m_isWriteable;
}

bool UIInputField::isFieldEnd()
{
	//get the bounds of the input text
	sf::FloatRect textBounds = m_inputText.getGlobalBounds();

	//check if it's bound of field
	if (textBounds.width > m_fieldBackground.getSize().x - (m_characterSizeOriginal + m_cursor.getSize().x + CURSOR_OFFSET + INPUT_TEXT_OFFSET))
	{
		LOG("Couldn't input more text because it's the end of the field");
		return true;
	}
	else
	{
		return false;
	}
}

void UIInputField::cursorMovement()
{
	//reposition cursor in case text changes
	sf::FloatRect textBounds = m_inputText.getGlobalBounds();
	m_cursor.setPosition(textBounds.left + textBounds.width + CURSOR_OFFSET,
		m_fieldBackground.getPosition().y + (m_fieldBackground.getSize().y - m_inputText.getCharacterSize()) / 2);
}

void UIInputField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//draw field
	target.draw(m_fieldBackground, states);

	//draw text
	target.draw(m_inputText, states);

	//draw cursor
	target.draw(m_cursor, states);
}

void UIInputField::handleResize(const sf::Vector2f& scale) {

	setCharactersSize(static_cast<uint32_t>(m_inputText.getCharacterSize() * scale.x));

	setSize(sf::Vector2f((getSize().x) * scale.x, (getSize().y) * scale.y));

	setPosition(sf::Vector2f((getPosition().x) * scale.x, (getPosition().y) * scale.y));
}
