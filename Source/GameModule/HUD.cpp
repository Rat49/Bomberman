#include "HUD.hpp"
#include "UISystem/UIFactory.hpp"
#include "UISystem/UILabel.hpp"

namespace
{
const std::string TIME_VALUE       = "TIME_VALUE";
const std::string SCORE            = "SCORE";
const std::string LIVES_LEFT_VALUE = "LIVES_LEFT_VALUE";
} // namespace

HUD::HUD(sf::RenderWindow* renderWindow, const std::string& hudFont, const std::string& pathToIniFile) : UIScreen()
{
    setWindow(renderWindow);

    UIFactory::makeScreen(pathToIniFile, this, hudFont);
}

// Set new value for Time
void HUD::setTime(const std::string& newTime)
{
    auto timeLabel = std::dynamic_pointer_cast<UILabel>(getElement(TIME_VALUE));
    if (timeLabel)
        timeLabel->setText(newTime);
}

// Set new value for Score
void HUD::setScore(const std::string& newScore)
{
    auto scoreLabel = std::dynamic_pointer_cast<UILabel>(getElement(SCORE));
    if (scoreLabel)
        scoreLabel->setText(newScore);
}

// Set new value for Lives Left
void HUD::setLivesLeft(const std::string& newLivesLeft)
{
    auto livesLeftLabel = std::dynamic_pointer_cast<UILabel>(getElement(LIVES_LEFT_VALUE));
    if (livesLeftLabel)
        livesLeftLabel->setText(newLivesLeft);
}
