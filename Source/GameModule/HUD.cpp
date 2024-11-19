#include "HUD.hpp"
#include "UISystem/UILabel.hpp"
#include "UISystem/UIFactory.hpp"

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

HUD::HUD(sf::RenderWindow* renderWindow, const std::string& hudFont, const std::string& pathToIniFile) : UIScreen()
{
	setWindow(renderWindow);

	UIFactory::getInstance().makeScreen(pathToIniFile, this, hudFont);
}

// Set new value for Time
void HUD::setTime(const std::string& newTime)
{
	auto timeLabel = std::dynamic_pointer_cast<UILabel>(getElement(TIME_VALUE));
	if(timeLabel)
		timeLabel->setText(newTime);
}

// Set new value for Score
void HUD::setScore(const std::string& newScore)
{
	auto scoreLabel = std::dynamic_pointer_cast<UILabel>(getElement(SCORE));
	if(scoreLabel)
		scoreLabel->setText(newScore);
}

// Set new value for Lives Left
void HUD::setLivesLeft(const std::string& newLivesLeft)
{
	auto livesLeftLabel = std::dynamic_pointer_cast<UILabel>(getElement(LIVES_LEFT_VALUE));
	if (livesLeftLabel)
		livesLeftLabel->setText(newLivesLeft);
}
