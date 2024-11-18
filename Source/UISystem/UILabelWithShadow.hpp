#include "UILabel.hpp"

class UILabelWithShadow : public UILabel
{
public:
	UILabelWithShadow(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Color& labelColor, const sf::Color& shadowColor);

	void setPosition(const sf::Vector2f& pos) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setText(const std::string& text) override;
private:
	sf::Text shadowText;
};