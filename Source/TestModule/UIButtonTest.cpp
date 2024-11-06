#include "TestModule/UIButtonTest.hpp"
#include "Common/Logs.hpp"

const std::string& UIButtonTest::getName() const
{
	return Name;
}

void UIButtonTest::setup()
{
	LOG("UIButtonTest: setup()");

	sf::Font& font = UIScreen::getFont("arial");

	// Create a UILabel and set some basic text
	button = std::make_shared<UIButton>("Click Me", font, 30);
	button->setPosition(sf::Vector2f(200.0f, 200.0f));
	button->setSize(sf::Vector2f(150.0f, 50.0f));

	// Set onHover event
	button->onHover = []()
		{
			LOG("UIButton is hovered!");
		};

	// Set onClick event
	button->onClick = []()
		{
			LOG("UIButton was clicked!");
		};

	screen.addElement(button);
}

void UIButtonTest::run()
{
	LOG("UIButtonTest: run()");
	if (button->getText() == "Click Me")
	{
		LOG("UIButtonTest: Text set successfully");
	}
	else
	{
		LOG("UIButtonTest: Text set failed");
	}
}

void UIButtonTest::update(float deltaTime, sf::RenderWindow* window)
{
	// Set the window for the screen instance if it's not set
	if (window && !screen.getWindow())
	{
		screen.setWindow(window);
	}

	// Handle events
	sf::Event event;

	// Handle hover and click for the button
	button->handleEvent(event);

	// Drawing simulation
	if (window)
	{
		deltaTime = 0.0f;

		window->clear(sf::Color::Red);

		// Draw all elements on the UIScreen
		screen.draw(*window, sf::RenderStates::Default);

		window->display();
	}

	// Mark the test as complete
	//completed = true;
}

bool UIButtonTest::isComplete() const
{
	return completed;
}
