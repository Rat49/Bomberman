#pragma once

#include "UISystem/UIElement.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <functional>

class UISlider : public UIElement
{
public:
	UISlider(const sf::Vector2f& size, float minValue = 0.0f, float maxValue = 100.0f);

	// Setters
	void setValue(float value);
	void setPosition(const sf::Vector2f& newPosition) override;
	void setSize(const sf::Vector2f& size);

	void setBarColor(const sf::Color& color);
	void setKnobColor(const sf::Color& color);

	// Getters
	float getValue() const;

	// Handle events for dragging the knob
	bool handleEvent(const sf::Event& event) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::function<void(float)> onValueChanged;

private:
	sf::RectangleShape bar;
	sf::CircleShape knob;

	float minValue;
	float maxValue;
	float currentValue;

	bool isDragging = false;
};
