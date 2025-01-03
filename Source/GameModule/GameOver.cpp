#include "GameOver.hpp"
#include "Common/Modules.hpp"
#include "GameModule.hpp"
#include "GameModule/MusicFactory.hpp"
#include "SoundSystem/SoundSystem.hpp"
#include "UIConstants.hpp"
#include "UISystem/UIButton.hpp"
#include "UISystem/UIFactory.hpp"
#include "UISystem/UIInputField.hpp"
#include "UISystem/UILabel.hpp"

namespace
{
const std::string SCORE        = "ScoreValue";
const std::string INITIAL_TEXT = "Enter name";
} // namespace

GameOver::GameOver(sf::RenderWindow* renderWindow, const std::string& screenFont, const std::string& pathToIniFile)
{
    setWindow(renderWindow);

    UIFactory::makeScreen(pathToIniFile, this, screenFont);

    for (auto& element : elements)
    {
        if (std::shared_ptr<UIButton> button = std::dynamic_pointer_cast<UIButton>(element.second))
        {
            button->onHover = [button]() { button->dropShadows(Colors::YELLOW, Colors::RED); };
            button->onClick = [button]() { button->dropShadows(Colors::RED, Colors::YELLOW); };

            if (element.first == Buttons::MENU)
            {
                button->onRelease = [this]()
                {
                    if (saveResult())
                    {
                        Modules::Game->setCurrentScreen(Screens::MAIN_MENU);
                        Modules::Sounds->playMusic(static_cast<int32_t>(AllMusic::Title));
                    }
                    else
                        invalidClickMenu = true;
                };
            }
        }
    }
}

bool GameOver::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::Resized)
    {
        return UIScreen::handleEvent(event);
    }
    for (auto& element : elements)
    {
        if (std::shared_ptr<UIButton> button = std::dynamic_pointer_cast<UIButton>(element.second))
        {
            if (button->isVisible() && !button->handleEvent(event))
            {
                button->dropShadows(Colors::WHITE, Colors::GREY);
            }
        }
        else if (std::shared_ptr<UIInputField> inputField = std::dynamic_pointer_cast<UIInputField>(element.second))
        {
            if (inputField->isVisible() && inputField->handleEvent(event))
            {
                inputField->setColor(Colors::WHITE, Colors::RED);
                playerName = inputField->getText();
            }
            if (invalidClickMenu)
            {
                inputField->setColor(Colors::RED, Colors::WHITE);

                inputField->setText(INITIAL_TEXT);
                inputField->setInitialText(INITIAL_TEXT);
                inputField->setHasPlaceholder(true);

                invalidClickMenu = false;
            }
        }
    }
    return true;
}

void GameOver::setScore(int32_t score)
{
    playerScore     = score;
    auto scoreLabel = std::dynamic_pointer_cast<UILabel>(getElement(SCORE));
    if (scoreLabel)
        scoreLabel->setText(std::to_string(score));
}

bool GameOver::saveResult()
{
    if (playerName.empty())
        return false;

    //save to file
    Modules::Game->addScore(playerScore, playerName);
    return true;
}
