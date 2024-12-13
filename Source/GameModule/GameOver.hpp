#pragma once
#include "UISystem/UIScreen.hpp"

class GameOver : public UIScreen
{
public:
    GameOver(sf::RenderWindow* renderWindow, const std::string& screenFont, const std::string& pathToIniFile);

    bool handleEvent(const sf::Event& event) override;

    void setScore(int32_t score);

private:
    bool saveResult();

    int32_t     playerScore = 0;
    std::string playerName;

    bool triedBack = false;


};