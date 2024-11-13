#include "TestModule/UILabelTest.hpp"
#include "Common/Logs.hpp"

const std::string& UILabelTest::getName() const
{
	return Name;
}

void UILabelTest::setup()
{
	LOG("UILabelTest: setup()");

	sf::Font& font = UIScreen::getFont("arial");

	// Create a UILabel and set some basic text
	label = std::make_unique<UILabel>("Test Label", font, 30);
	label->setText("Test Label");
	label->setPosition(sf::Vector2f(100.0f, 100.0f));

	// Set onHover event
	label->onHover = []()
		{
			LOG("UILabel is hovered!");
		};

	screen.addElement(label);
}

void UILabelTest::run()
{
	LOG("UILabelTest: run()");
	if (label->getText() == "Test Label")
	{
		LOG("UILabelTest: Text set successfully");
	}
	else
	{
		LOG("UILabelTest: Text set failed");
	}
}

void UILabelTest::update(float deltaTime, sf::RenderWindow* window)
{
	// Set the window for the screen instance if it's not set
	if (window && !screen.getWindow())
	{
		screen.setWindow(window);
	}

	// Drawing simulation
	if (window)
	{
		deltaTime = 0.0f;
		LOG("UILabelTest: Label drawn at position (100, 100)");

		// Set background color to red
		window->clear(sf::Color::Red);

		// Draw all elements on the UIScreen
		screen.draw(*window, sf::RenderStates::Default);

		window->display();
	}

	// Mark the test as complete
	completed = true;
}

bool UILabelTest::isComplete() const
{
	return completed;
}
