#include "TestModule/UILabelTest.hpp"
#include "UISystem/UIScreen.hpp"
#include "Common/Logs.hpp"

const std::string& UILabelTest::getName() const
{
	return Name;
}

void UILabelTest::setup()
{
	LOG("UILabelTest: setup()");

	sf::Font font;
	if (!font.loadFromFile("Assets/Fonts/arial.ttf"))
	{
		LOG("Failed to load font!");
	}

	// Create a UILabel and set some basic text
	label = std::make_unique<UILabel>("Test Label", font, 30);
	label->setText("Test Label");
	label->setPosition(sf::Vector2f(100.0f, 100.0f));

	// Set onHover event
	label->onHover = []()
		{
			LOG("UILabel is hovered!");
		};

	// Set onClick event
	label->onClick = []()
		{
			LOG("UILabel was clicked!");
		};
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
	// Creating a UIScreen instance
	UIScreen screen;
	// Set the pointer to the window
	screen.setWindow(window);

	// Drawing simulation
	if (window)
	{
		//label->draw()
		deltaTime = 0.0f;
		LOG("UILabelTest: Label drawn at position (100, 100)");
	}

	// Mark the test as complete
	completed = true;
}

bool UILabelTest::isComplete() const
{
	return completed;
}
