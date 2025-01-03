#pragma once
#include "UISystem/UIScreen.hpp"

class StageScreen : public UIScreen
{
public:
    StageScreen(sf::RenderWindow* renderWindow, const std::string& hudFont, const std::string& pathToIniFile);

    void setStage(int32_t newStage);
};