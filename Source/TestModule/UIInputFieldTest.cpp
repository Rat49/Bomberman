#include "UIInputFieldTest.hpp"
#include "UISystem/UIScreen.hpp"
#include "UISystem/UIInputField.hpp"
#include "UISystem/UILabel.hpp"
#include "Common/Logs.hpp"

namespace {
	const std::string FONT_NAME = "bomberman";
}

const std::string& UIInputFieldTest::getName() const
{
	return m_name;
}

void UIInputFieldTest::setup()
{
	//screen
	m_screen = std::make_shared<UIScreen>();
	auto& font = m_screen->getFont("arial");

	//input field
	m_inputField = std::make_shared<UIInputField>(font, 20, sf::Vector2f(200.0f, 80.0f));
	m_inputField->setPosition(sf::Vector2f(20.f, 20.f));

	m_screen->addElement("inputField", m_inputField);

	//label
	m_label = std::make_shared<UILabel>("Text from input field" , font, 20);
	m_label->setPosition(sf::Vector2f(20.f, 140.f));

	m_screen->addElement("label", m_label);
}

void UIInputFieldTest::run()
{
	LOG("UI Input field test run");
}

void UIInputFieldTest::update(float, sf::RenderWindow* window)
{
	//set the window for the screen
	if (window && !m_screen->getWindow())
	{
		m_screen->setWindow(window);
	}


	//handle events
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			m_inputField->handleEvent(event);
		}
		else if (event.type == sf::Event::TextEntered)
		{
			if (m_inputField->handleEvent(event))
			{
				m_label->setText(m_inputField->getText());
			}
		}
		else if (event.type == sf::Event::Resized)
		{
			Modules::UI->setViewportSize((float)(m_screen->getWindow()->getSize().x), (float)(m_screen->getWindow()->getSize().y));
			m_screen->handleEvent(event);
		}
	}

	//draw 
	if (window)
	{
		window->clear(sf::Color::Red);
		m_screen->draw(*window, sf::RenderStates::Default);
		window->display();
	}

	m_isCompleted = false;
}

bool UIInputFieldTest::isComplete() const
{
	return m_isCompleted;
}
