#pragma once
#include "UISystem/UIScreen.hpp"

class Options : public UIScreen
{
public:
	Options(sf::RenderWindow* renderWindow, const std::string& optionsFont, const std::string& pathToIniFile);

	bool handleEvent(const sf::Event& event) override;

	void showAudio();
};