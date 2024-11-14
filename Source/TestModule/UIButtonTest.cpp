#include "TestModule/UIButtonTest.hpp"
#include "Common/Logs.hpp"

// FOR TESTING: comment out the lines in the GameModule.cpp script from lines 35. to 41. and from lines 49. to 51.
// FOR TESTING: Uncomment the lines in this class from 191. to 199. and line 202.

const std::string& UIButtonTest::getName() const
{
	return Name;
}

void UIButtonTest::setup()
{
	LOG("UIButtonTest: setup()");

	sf::Font& font = UIScreen::getFont("arial");

	screen1 = std::make_shared<UIScreen>();

	// Create a UIButton and set some basic text
	button = std::make_shared<UIButton>("Click Me 1", font, 20, sf::Vector2f(120.0f, 50.0f));
	button->setPosition(sf::Vector2f(0.0f, 0.0f));

	// Set different colors for different states of the button
	button->setDefaultColor(sf::Color::Green);
	button->setHoverColor(sf::Color::Yellow);
	button->setPressedColor(sf::Color::Blue);
	screen1->addElement(button);

	// Button 2 overlaps Button 3
	button2 = std::make_shared<UIButton>("Button 2", font, 20, sf::Vector2f(100.0f, 50.0f));
	button2->setPosition(sf::Vector2f(100.0f, 100.0f));

	// Set different colors for different states of the button
	button2->setDefaultColor(sf::Color::Green);
	button2->setHoverColor(sf::Color::Yellow);
	button2->setPressedColor(sf::Color::Blue);
	screen1->addElement(button2);

	// Button 3 overlaps Button 2
	button3 = std::make_shared<UIButton>("Button 3", font, 20, sf::Vector2f(100.0f, 50.0f));
	button3->setPosition(sf::Vector2f(120.0f, 120.0f));

	// Set different colors for different states of the button
	button3->setDefaultColor(sf::Color::Green);
	button3->setHoverColor(sf::Color::Yellow);
	button3->setPressedColor(sf::Color::Blue);
	screen1->addElement(button3);

	// Button 4 overlaps with Label 4
	button4 = std::make_shared<UIButton>("Button 4", font, 20, sf::Vector2f(100.0f, 50.0f));
	button4->setPosition(sf::Vector2f(200.0f, 200.0f));

	// Set different colors for different states of the button
	button4->setDefaultColor(sf::Color::Green);
	button4->setHoverColor(sf::Color::Yellow);
	button4->setPressedColor(sf::Color::Blue);
	screen1->addElement(button4);

	// Creating and placing labels
	// Label 1 is independent
	label1 = std::make_shared<UILabel>("Label 1", font, 20);
	label1->setPosition(sf::Vector2f(300.0f, 0.0f)); 
	screen1->addElement(label1);

	// Label 2 overlaps with Label 3
	label2 = std::make_shared<UILabel>("Label 2", font, 20);
	label2->setPosition(sf::Vector2f(150.0f, 300.0f));
	screen1->addElement(label2);

	// Label 3 overlaps with Label 2
	label3 = std::make_shared<UILabel>("Label 3", font, 20);
	label3->setPosition(sf::Vector2f(160.0f, 310.0f));
	screen1->addElement(label3);

	// Label 4 overlaps Button 4
	label4 = std::make_shared<UILabel>("Label 4", font, 20);
	label4->setPosition(sf::Vector2f(210.0f, 210.0f));
	screen1->addElement(label4);

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

	button2->onHover = []()
		{
			LOG("UIButton is hovered!");
		};

	button2->onClick = []()
		{
			LOG("UIButton was clicked!");
		};

	button3->onHover = []()
		{
			LOG("UIButton is hovered!");
		};

	button3->onClick = []()
		{
			LOG("UIButton was clicked!");
		};

	button4->onHover = []()
		{
			LOG("UIButton is hovered!");
		};

	button4->onClick = []()
		{
			LOG("UIButton was clicked!");
		};
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
	(void)deltaTime;

	// Handle events
	sf::Event event;

	// Set the window for the screen instance if it's not set
	if (window && !screen1->getWindow())
	{
		screen1->setWindow(window);
	}

	// Handle hover and click for the button
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			//LOG("MouseButtonPressed event detected");
			button->handleEvent(event);
			button2->handleEvent(event);
			button3->handleEvent(event);
			button4->handleEvent(event);
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			//LOG("MouseButtonReleased event detected");
			button->handleEvent(event);
			button2->handleEvent(event);
			button3->handleEvent(event);
			button4->handleEvent(event);
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			//LOG("MouseMoved event detected");
			button->handleEvent(event);
			button2->handleEvent(event);
			button3->handleEvent(event);
			button4->handleEvent(event);
		}
		else if (event.type == sf::Event::Resized)
		{
			Modules::UI->setViewportSize((float)(screen1->getWindow()->getSize().x), (float)(screen1->getWindow()->getSize().y));

			screen1->handleEvent(event);
		}
	}

	// Drawing simulation
	//if (window)
	//{
	//	window->clear(sf::Color::Red);

	//	// Draw all elements on the UIScreen
	//	screen1->draw(*window, sf::RenderStates::Default);

	//	window->display();
	//}

	// Mark the test as complete
	//completed = true;
}

bool UIButtonTest::isComplete() const
{
	return completed;
}
