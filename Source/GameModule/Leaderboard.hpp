#pragma once
#include "UISystem/UIScreen.hpp"

class Leaderboard : public UIScreen
{
public:

	Leaderboard(sf::RenderWindow* renderWindow, const std::string& hudFont, const std::string& pathToIniFile);

	void readLeaderboard();

	bool handleEvent(const sf::Event& event) override;
};