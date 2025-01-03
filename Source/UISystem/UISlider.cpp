#include "UISystem/UISlider.hpp"

UISlider::UISlider(const sf::Vector2f& size, float minValue, float maxValue)
    : minValue(minValue), maxValue(maxValue), currentValue(minValue)
{
    setSize(size);
    bar.setFillColor(sf::Color::White);
    knob.setFillColor(sf::Color::Black);
}

void UISlider::setValue(float value)
{
    currentValue        = std::clamp(value, minValue, maxValue);
    float progressRatio = (currentValue - minValue) / (maxValue - minValue);
    knob.setPosition(bar.getPosition().x + bar.getSize().x * progressRatio,
                     bar.getPosition().y + bar.getSize().y / (bar.getSize().y / 2));

    if (onValueChanged)
    {
        onValueChanged(currentValue);
    }
}

void UISlider::setPosition(const sf::Vector2f& newPosition)
{
    UIElement::setPosition(newPosition);
    bar.setPosition(newPosition);
    setValue(currentValue);
}

void UISlider::setSize(const sf::Vector2f& size)
{
    UIElement::setSize(size);
    bar.setSize(size);

    // Align vertically
    bar.setOrigin(0.f, size.y / 2.f);

    // Knob radius -> smaller than bar (so 0.8f) and bar has height of (size.y / 2.f)
    knob.setRadius(size.y * 0.8f / 2.f);
    knob.setOrigin(knob.getRadius(), knob.getRadius());

    setValue(currentValue);
}

void UISlider::setBarColor(const sf::Color& color)
{
    bar.setFillColor(color);
}

void UISlider::setKnobColor(const sf::Color& color)
{
    knob.setFillColor(color);
}

float UISlider::getValue() const
{
    return currentValue;
}

bool UISlider::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (knob.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x),
                                            static_cast<float>(event.mouseButton.y)))
        {
            isDragging = true;
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
        if (isDragging && onReleased)
        {
            onReleased();
        }
        isDragging = false;
    }
    else if (event.type == sf::Event::MouseMoved && isDragging)
    {
        float mouseX        = static_cast<float>(event.mouseMove.x);
        float progressRatio = (mouseX - bar.getPosition().x) / bar.getSize().x;
        setValue(minValue + progressRatio * (maxValue - minValue));
    }

    return isDragging;
}

void UISlider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(bar, states);
    target.draw(knob, states);
}

void UISlider::handleResize(const sf::Vector2f& scale)
{

    setSize(sf::Vector2f((getSize().x) * scale.x, (getSize().y) * scale.y));

    setPosition(sf::Vector2f((getPosition().x) * scale.x, (getPosition().y) * scale.y));
}
