#include "UICheckbox.hpp"

UICheckbox::UICheckbox(float size)
{
    setSize(size);
    setIsInteractable(true);
    checkboxOutsideRectangle.setFillColor(defaultColorOutsideRect);
    checkboxInsideRectangle.setFillColor(defaultColorInsideRect);
}

void UICheckbox::setPosition(const sf::Vector2f& pos)
{
    UIElement::setPosition(pos);
    m_pos = pos;
    sf::Vector2f v2(pos.x, pos.y);
    float        difference = ((m_size - (m_size * m_factor))) / 2.0f;
    sf::Vector2f offset(difference, difference);
    checkboxOutsideRectangle.setPosition(pos);
    checkboxInsideRectangle.setPosition(pos + offset);
}

void UICheckbox::setSize(float edgeSize)
{
    sf::Vector2f outsideRectangleSize(edgeSize, edgeSize);
    sf::Vector2f insideRectangleSize(edgeSize * m_factor, edgeSize * m_factor);
    UIElement::setSize(outsideRectangleSize);
    checkboxInsideRectangle.setSize(insideRectangleSize);
    checkboxOutsideRectangle.setSize(outsideRectangleSize);
    m_size = edgeSize;
}

void UICheckbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(checkboxOutsideRectangle, states);
    if (m_isChecked)
    {
        target.draw(checkboxInsideRectangle, states);
    }
}

bool UICheckbox::handleEvent(const sf::Event& event)
{
    if (!getIsInteractable())
    {
        return false;
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        float mouseX = static_cast<float>(event.mouseButton.x);
        float mouseY = static_cast<float>(event.mouseButton.y);
        if (containsPoint(sf::Vector2f(mouseX, mouseY)) && !m_isHolding)
        {
            m_isChecked = !m_isChecked;
            m_isHolding = true;
            if (onClick)
            {
                onClick();
            }
        }
    }
    else if (m_isHolding)
    {
        m_isHolding = false;
    }

    if (event.type == sf::Event::MouseMoved)
    {
        float mouseX = static_cast<float>(event.mouseMove.x);
        float mouseY = static_cast<float>(event.mouseMove.y);

        m_isHovered = containsPoint(sf::Vector2f(mouseX, mouseY));

        if (m_isHovered)
        {
            LOG("Hover callback called.");
            checkboxOutsideRectangle.setFillColor(hoverColorOutsideRect);
            if (onHover)
            {
                onHover();
            }
        }
        else
        {
            checkboxOutsideRectangle.setFillColor(defaultColorOutsideRect);
        }
    }

    return false;
}

void UICheckbox::setDefaultColorOutsideRect(const sf::Color& color)
{
    defaultColorOutsideRect = color;
    checkboxOutsideRectangle.setFillColor(defaultColorOutsideRect);
}

void UICheckbox::setHoverColorOutsideRect(const sf::Color& color)
{
    hoverColorOutsideRect = color;
}

void UICheckbox::setDefaultColorInsideRect(const sf::Color& color)
{
    defaultColorInsideRect = color;
    checkboxInsideRectangle.setFillColor(defaultColorInsideRect);
}

void UICheckbox::setFactor(float factor)
{
    if (factor < 1.0f && factor > 0.1f)
    {
        m_factor = factor;
        sf::Vector2f insideRectangleSize(m_size * m_factor, m_size * m_factor);
        checkboxInsideRectangle.setSize(insideRectangleSize);
        float        difference = ((m_size - (m_size * m_factor))) / 2.0f;
        sf::Vector2f offset(difference, difference);
        checkboxInsideRectangle.setPosition(m_pos + offset);
    }
}