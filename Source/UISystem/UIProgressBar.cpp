#include "UISystem/UIProgressBar.hpp"

UIProgressBar::UIProgressBar(const sf::Vector2f& newSize, float newMinValue, float newMaxValue)
    : minValue(newMinValue), maxValue(newMaxValue), currentValue(minValue)
{
    setSize(newSize);
    background.setFillColor(sf::Color::White);
    background.setOutlineThickness(2.0f);
    background.setOutlineColor(sf::Color::Black);
    fill.setFillColor(sf::Color::Green);
}

void UIProgressBar::setProgress(float value)
{
    currentValue        = std::clamp(value, minValue, maxValue);
    float progressRatio = (currentValue - minValue) / (maxValue - minValue);
    fill.setSize({background.getSize().x * progressRatio, background.getSize().y});
}

void UIProgressBar::setPosition(const sf::Vector2f& newPosition)
{
    background.setPosition(newPosition);
    fill.setPosition(newPosition);
}

void UIProgressBar::setSize(const sf::Vector2f& size)
{
    background.setSize(size);

    // Adjust fill size based on current progress
    setProgress(currentValue);
}

void UIProgressBar::setFillColor(const sf::Color& color)
{
    fill.setFillColor(color);
}

void UIProgressBar::setBackgroundColor(const sf::Color& color)
{
    background.setFillColor(color);
}

void UIProgressBar::setBorderColor(const sf::Color& color)
{
    background.setOutlineColor(color);
}

float UIProgressBar::getProgress() const
{
    return currentValue;
}

sf::Vector2f UIProgressBar::getSize() const
{
    return background.getSize();
}

void UIProgressBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(background, states);
    target.draw(fill, states);
}

bool UIProgressBar::handleEvent(const sf::Event& event)
{
    // Logic for event handling goes here

    (void)event;

    return false;
}
