#include "TestModule/UIProgressBarTest.hpp"
#include "AssetManager/AssetManager.hpp"
#include "Common/Logs.hpp"
#include "Common/Modules.hpp"

// FOR TESTING: the event, display, draw and clear functions in GameModule.cpp must be commented out

namespace
{
const std::string FONT_PATH = "Game/Fonts/arial.ttf";
}

const std::string& UIProgressBarTest::getName() const
{
    return Name;
}

void UIProgressBarTest::setup()
{
    LOG("UIProgressBarAndSliderTest: setup()");

    std::shared_ptr<sf::Font> font = Modules::Assets->getFont(FONT_PATH);

    if (!font)
    {
        LOG("Failed to load font from path : [$]", FONT_PATH);
        return;
    }

    // Create UIScreen
    screen = std::make_shared<UIScreen>();

    // Create and configure ProgressBar
    progressBar = std::make_shared<UIProgressBar>(sf::Vector2f(300.0f, 30.0f), 0.0f, 100.0f); // min = 0, max = 100
    progressBar->setPosition(sf::Vector2f(100.0f, 50.0f));
    progressBar->setFillColor(sf::Color::Green);
    progressBar->setBackgroundColor(sf::Color::Black);
    progressBar->setProgress(50.0f);
    screen->addElement("progressBar", progressBar);

    // Create and configure Slider
    slider = std::make_shared<UISlider>(sf::Vector2f(300.0f, 30.0f), 0.0f, 100.0f);
    slider->setPosition(sf::Vector2f(100.0f, 150.0f));
    slider->setBarColor(sf::Color::Blue);
    slider->setKnobColor(sf::Color::Yellow);

    // Match ProgressBar initial value
    slider->setValue(50.0f);
    screen->addElement("slider", slider);

    // Link Slider and ProgressBar behavior
    slider->onValueChanged = [this](float value)
    {
        LOG("Slider value changed to: $", value);

        // Update progress bar based on slider value
        progressBar->setProgress(value);
    };
}

void UIProgressBarTest::run()
{
    LOG("UIProgressBarAndSliderTest: run()");
    if (progressBar->getProgress() == 50.0f && slider->getValue() == 50.0f)
    {
        LOG("Initial values are set correctly.");
    }
    else
    {
        LOG("Initial values are incorrect.");
    }
}

void UIProgressBarTest::update(float deltaTime, sf::RenderWindow* window)
{
    (void)deltaTime;

    // Handle events
    sf::Event event;

    // Set the window for the screen instance if it's not set
    if (window && !screen->getWindow())
    {
        screen->setWindow(window);
    }

    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            slider->handleEvent(event);
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            slider->handleEvent(event);
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            slider->handleEvent(event);
        }

        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
    }

    // Drawing simulation
    if (window)
    {
        window->clear(sf::Color::White);

        // Draw all elements on the UIScreen
        screen->draw(*window, sf::RenderStates::Default);

        window->display();
    }

    // Check if test is complete
    completed = slider->getValue() >= 100.0f;
}

bool UIProgressBarTest::isComplete() const
{
    return completed;
}
