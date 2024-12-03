#pragma once

#include "UISystem/UIElement.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class UIProgressBar : public UIElement
{
public:
	UIProgressBar(const sf::Vector2f& newSize, float newMinValue = 0.0f, float newMaxValue = 100.0f);

	// Setters
	void setProgress(float value);
	void setPosition(const sf::Vector2f& newPosition) override;
	void setSize(const sf::Vector2f& barSize);

	// Getters
	float getProgress() const;
	sf::Vector2f getSize() const;

	void setFillColor(const sf::Color& fillColor);
	void setBackgroundColor(const sf::Color& bgColor);
	void setBorderColor(const sf::Color& borderColor);

	bool handleEvent(const sf::Event& event) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::RectangleShape background;
	sf::RectangleShape fill;

	float minValue;
	float maxValue;
	float currentValue;
};
