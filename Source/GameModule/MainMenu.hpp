#pragma once
#include "UISystem/UIScreen.hpp"

class MainMenu : public UIScreen
{
public:
    MainMenu(sf::RenderWindow* renderWindow, const std::string& font, const std::string& pathToIniFile);

    bool handleEvent(const sf::Event& event) override;
};