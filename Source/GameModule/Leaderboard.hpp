#pragma once
#include "UISystem/UIScreen.hpp"

class Leaderboard : public UIScreen
{
public:

	Leaderboard(sf::RenderWindow* renderWindow, const std::string& hudFont, const std::string& pathToIniFile);

	void readLeaderboard();

	bool handleEvent(const sf::Event& event) override;

	void addScore(int32_t newScore, const std::string& name);

	void saveResults();

private:
    std::vector<std::pair<std::string, int32_t>> results;
};
