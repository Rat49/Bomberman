#include "UILabelWithShadow.hpp"

UILabelWithShadow::UILabelWithShadow(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Color& labelColor, const sf::Color& shadowColor) : UILabel(text, font, characterSize)
{
	shadowText.setFont(font);
	shadowText.setString(text);
	shadowText.setCharacterSize(characterSize);

	labelText.setFillColor(labelColor);
	shadowText.setFillColor(shadowColor);
}

void UILabelWithShadow::setPosition(const sf::Vector2f& pos)
{
	UILabel::setPosition(pos);

	float offset = (shadowText.getCharacterSize() + 0.f) / 10;
	shadowText.setPosition(sf::Vector2f(pos.x + offset, pos.y + offset));

}

void UILabelWithShadow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (isVisible())
	{
		target.draw(shadowText, states);
		target.draw(labelText, states);
	}
}

void UILabelWithShadow::setText(const std::string& text)
{
	UILabel::setText(text);
	shadowText.setString(text);
}
