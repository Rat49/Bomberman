#include "HUD.hpp"
#include "UISystem/UILabelWithShadow.hpp"

namespace {
	const std::string& TIME = "TIME";
	const std::string& TIME_VALUE = "TIME VALUE";
	const std::string& STARTING_TIME_VALUE = "200";
	const std::string& SCORE = "SCORE";
	const std::string& STARTING_SCORE = "00";
	const std::string& LIVES_LEFT = "LEFT";
	const std::string& LIVES_LEFT_VALUE = "LEFT VALUE";
	const std::string& STARTING_LIVES_LEFT_VALUE = "2";
}

HUD::HUD(sf::RenderWindow* renderWindow, const std::string& hudFont) : UIScreen()
{
	setWindow(renderWindow);

	const sf::Font& font = getFont(hudFont);
	
	const sf::Color& labelColor = sf::Color::White;
	const sf::Color& shadowColor = sf::Color::Black;

	const int32_t width = renderWindow->getSize().x;
	const int32_t heigth = renderWindow->getSize().y;

	auto characterSize = static_cast<unsigned int>(0.0375 * width);

	std::vector<std::string> labelNames = { TIME, STARTING_TIME_VALUE, STARTING_SCORE, LIVES_LEFT, STARTING_LIVES_LEFT_VALUE};
	std::vector<std::string> elementNames = { TIME, TIME_VALUE, SCORE, LIVES_LEFT, LIVES_LEFT_VALUE };
	std::vector<float> offsets = { 0.025f, 0.2f, 0.5f, 0.7625f, 0.9375f };

	// Adding all elements in a map
	std::shared_ptr<UILabelWithShadow> myLabel;
	for (int32_t i = 0; i < labelNames.size(); i++) {
		myLabel = std::make_unique<UILabelWithShadow>(labelNames[i], font, characterSize, labelColor, shadowColor);
		myLabel->setPosition(sf::Vector2f(offsets[i] * width, 0.017f * heigth));

		addElement(elementNames[i], myLabel);
	}
}

// Set new value for Time
void HUD::setTime(const std::string& newTime)
{
	std::shared_ptr<UILabelWithShadow> timeLabel = std::dynamic_pointer_cast<UILabelWithShadow>(getElement(TIME_VALUE));
	if(timeLabel)
		timeLabel->setText(newTime);
}

// Set new value for Score
void HUD::setScore(const std::string& newScore)
{
	std::shared_ptr<UILabelWithShadow> scoreLabel = std::dynamic_pointer_cast<UILabelWithShadow>(getElement(SCORE));
	if(scoreLabel)
		scoreLabel->setText(newScore);
}

// Set new value for Lives Left
void HUD::setLivesLeft(const std::string& newLivesLeft)
{
	std::shared_ptr<UILabelWithShadow> livesLeftLabel = std::dynamic_pointer_cast<UILabelWithShadow>(getElement(LIVES_LEFT_VALUE));
	if (livesLeftLabel)
		livesLeftLabel->setText(newLivesLeft);
}
