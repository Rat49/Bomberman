#include "Leaderboard.hpp"
#include "UISystem/UIFactory.hpp"
#include "Common/Modules.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "UISystem/UILabel.hpp"
#include "UISystem/UIButton.hpp"
#include "GameModule/GameModule.hpp"
#include "Common/Logs.hpp"
#include "SaveSystem/SaveSystem.hpp"
#include "SoundSystem/SoundSystem.hpp"
#include "GameModule/MusicFactory.hpp"

namespace
{
	const std::string PLAYER = "Player";
	const std::string NAME = "Name";
	const std::string VALUE = "Value";
    const std::string FILE_NAME  = "leaderboardResults";
    const int32_t numberOfPlayers = 5;   // number of players that are written on leader board screen
    }

Leaderboard::Leaderboard(sf::RenderWindow* renderWindow, const std::string& hudFont, const std::string& pathToIniFile) : UIScreen()
{
	setWindow(renderWindow);

	UIFactory::makeScreen(pathToIniFile, this, hudFont);

	readLeaderboard();

	std::shared_ptr<UIButton> menuButton = std::dynamic_pointer_cast<UIButton>(getElement(Buttons::MENU));

	menuButton->onHover = [menuButton]() {
		menuButton->dropShadows(Colors::YELLOW, Colors::RED);
		};
	menuButton->onClick = [menuButton]() {
		menuButton->dropShadows(Colors::RED, Colors::YELLOW);
		};
	menuButton->onRelease = []() {
		Modules::Game->setCurrentScreen(Screens::MAIN_MENU);
        Modules::Sounds->playMusic(static_cast<int32_t>(AllMusic::Title));
		};
}

void Leaderboard::readLeaderboard()
{
    std::unordered_map<std::string, std::string> dataMap;
	Modules::Save->loadGameData(FILE_NAME, dataMap);

	int32_t i = 1;
    while (i <= numberOfPlayers)
    {
        std::string playerName = PLAYER + std::to_string(i);
        std::string score      = playerName + VALUE;
        if (dataMap.count(playerName) && dataMap.count(score))
        {
            results.push_back({dataMap[playerName], std::stoi(dataMap[score])});

            // Setting name and result for that player
            (std::dynamic_pointer_cast<UILabel>(elements[playerName]))->setText(dataMap[playerName]);
            playerName += VALUE;
            (std::dynamic_pointer_cast<UILabel>(elements[score]))->setText(dataMap[score]);
        }
        else
        {
            // Setting for labels to not be visible as well as animation for that player
            (std::dynamic_pointer_cast<UILabel>(elements[playerName]))->setVisible(false);
            if (animations.count(playerName))
                animations[playerName]->Stop();
            (std::dynamic_pointer_cast<UILabel>(elements[score]))->setVisible(false);
        }
		

        i++;
    }
}

bool Leaderboard::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::Resized) {
		return UIScreen::handleEvent(event);
	}
	std::shared_ptr<UIButton> menuButton = std::dynamic_pointer_cast<UIButton>(getElement(Buttons::MENU));
	if (!menuButton->handleEvent(event)) {
		menuButton->dropShadows(Colors::WHITE, Colors::GREY);
	}
	return true;
}

void Leaderboard::addScore(int32_t newScore, const std::string& name)
{
    std::pair<std::string, int32_t> newResult = {name, newScore};

    for (int32_t i = 0; i < results.size(); i++)
    {
        if (results[i].second < newResult.second)
            std::swap(results[i], newResult);
        
    }
    if (results.size() < numberOfPlayers)
        results.push_back(newResult);

    int32_t i = 0;
    while (i < results.size())
    {
        std::string playerName = PLAYER + std::to_string(i+1);
        
        // Setting name and result for that player
        auto nameLabel = (std::dynamic_pointer_cast<UILabel>(elements[playerName]));
        nameLabel->setText(results[i].first);
        nameLabel->setVisible(true);

        if (animations.count(playerName))
            animations[playerName]->Play();
        playerName += VALUE;

        auto scoreLabel = (std::dynamic_pointer_cast<UILabel>(elements[playerName]));
        scoreLabel->setText(std::to_string(results[i].second));
        scoreLabel->setVisible(true);
       
        i++;
    }
}

void Leaderboard::saveResults()
{
    std::unordered_map<std::string, std::string> dataMap;
    int32_t                                      i = 0;
    while (i < results.size())
    {
        std::string playerName = PLAYER + std::to_string(i + 1);
        std::string score      = playerName + VALUE;
        dataMap[playerName]    = results[i].first;
        dataMap[score]         = std::to_string(results[i].second);
        i++;
    }
    Modules::Save->saveGameData(FILE_NAME, dataMap);
}
