#pragma once
#include "UISystem/UIElement.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class UICheckbox : public UIElement
{
public:
	explicit UICheckbox(float edgeSize);

	void setPosition(const sf::Vector2f& pos) override;

	void setSize(float edgeSize);

	bool isChecked() const { return m_isChecked; }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool handleEvent(const sf::Event& event) override;

	void setDefaultColorOutsideRect(const sf::Color& color);

	void setHoverColorOutsideRect(const sf::Color& color);

	void setDefaultColorInsideRect(const sf::Color& color);

	void setFactor(float factor);

	std::function<void()> onHover;

	std::function<void()> onClick;

private:
	bool m_isChecked = false;
	bool m_isHovered = false;
	bool m_isHolding = false;
	float m_size = 0.f;
	float m_factor = 0.7f;
	sf::Vector2f m_pos;
	sf::RectangleShape checkboxOutsideRectangle;
	sf::RectangleShape checkboxInsideRectangle;

	sf::Color defaultColorOutsideRect = sf::Color::White;
	sf::Color hoverColorOutsideRect   = sf::Color::Cyan;
	sf::Color defaultColorInsideRect  = sf::Color::Red;
};

