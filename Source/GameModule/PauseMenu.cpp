#include "PauseMenu.hpp"
#include "UISystem/UIButton.hpp"
#include "UISystem/UIFactory.hpp"
#include "Common/Modules.hpp"
#include "GameModule/GameModule.hpp"
#include "InputModule/InputModule.hpp"

namespace
{
	const sf::Color& WHITE = sf::Color::White;
	const sf::Color& GREY = sf::Color(128, 128, 128);
	const sf::Color& YELLOW = sf::Color(247, 190, 57);
	const sf::Color& RED = sf::Color(173, 0, 16);
	const std::string& RESUME = "RESUME";
	const std::string& MENU = "MENU";
}

PauseMenu::PauseMenu(sf::RenderWindow* renderWindow, const std::string& pauseFont, const std::string& pathToIniFile) 
{
	setWindow(renderWindow);

	UIFactory::makeScreen(pathToIniFile, this, pauseFont);

	handleInput();

	for (auto& element : elements) {
		if (std::shared_ptr<UIButton> button = std::dynamic_pointer_cast<UIButton>(element.second)) {
			button->onHover = [button]() {
				button->dropShadows(YELLOW, RED);
				};
			button->onClick = [button]() {
				button->dropShadows(RED, YELLOW);
				};
			if (element.first == RESUME) {
				button->onRelease = []() {
					Modules::Game->setIsPaused(false);
				};
			}
			else if (element.first == MENU) {
				button->onRelease = []() {
					Modules::Game->setCurrentScreen(Screens::MAIN_MENU);
				};
			}
		}
	}
}

bool PauseMenu::handleEvent(const sf::Event& event) 
{
	if (event.type == sf::Event::Resized) {
		view.setSize(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y));
		updateUIElementPositions();
	}
	for (auto& element : elements) {
		if (std::shared_ptr<UIButton> button = std::dynamic_pointer_cast<UIButton>(element.second)) {
			if (!button->handleEvent(event)) {
				button->dropShadows(WHITE, GREY);
			}
		}
	}
	return true;
}

void PauseMenu::handleInput()
{
	Modules::Input->LoadInputSettings("../../Data/Config/input_config.ini");

	pauseID = Modules::Input->GetActionID("Pause");
	if (pauseID < 0)
	{
		LOG("Failed to get Pause action ID.");
		return;
	}

	pauseHandle = Modules::Input->RegisterEvent(pauseID, std::bind(&PauseMenu::onPause, this, std::placeholders::_1));
	if (pauseHandle < 0)
	{
		LOG("Failed to register Pause event.");
		return;
	}
}

void PauseMenu::onPause(void* buttonState)
{
	bool state = *reinterpret_cast<bool*>(buttonState);
	if(state)
		Modules::Game->setIsPaused(true);
}
