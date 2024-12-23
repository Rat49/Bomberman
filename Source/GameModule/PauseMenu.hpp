#pragma once
#include "UISystem/UIScreen.hpp"
#include "InputModule/InputTypes.hpp"

class PauseMenu : public UIScreen
{
public:

	PauseMenu(sf::RenderWindow* renderWindow, const std::string& hudFont, const std::string& pathToIniFile);

	bool handleEvent(const sf::Event& event) override;

	void handleInput();

	void onPause(void* buttonState);

private:

	ActionID pauseID;
	FunctionHandle pauseHandle;
    bool isPauseMenuOpen = false;
};