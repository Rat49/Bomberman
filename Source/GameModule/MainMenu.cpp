#include "MainMenu.hpp"
#include "UISystem/UIFactory.hpp"
#include "UISystem/UIButton.hpp"
#include "Common/Logs.hpp"
#include "UIConstants.hpp"
#include "GameModule.hpp"

MainMenu::MainMenu(sf::RenderWindow* renderWindow, const std::string& font, const std::string& pathToIniFile) : UIScreen()
{
	setWindow(renderWindow);

	UIFactory::makeScreen(pathToIniFile, this, font);

	for (auto& element : elements) {
		if (std::shared_ptr<UIButton> button = std::dynamic_pointer_cast<UIButton>(element.second)) {
			button->onHover = [button]() {
				button->dropShadows(Colors::YELLOW, Colors::RED);
			};
			button->onClick = [button]() {
				button->dropShadows(Colors::RED, Colors::YELLOW);
			};
			if (element.first == Buttons::START) {
				button->onRelease = []() {
					Modules::Game->setCurrentScreen(Screens::STAGE);
				};
			}
			else if (element.first == Buttons::LEADERBOARD) {
				button->onRelease = []() {
					Modules::Game->setCurrentScreen(Screens::LEADERBOARD);
					};
			}
			else if (element.first == Buttons::OPTIONS) {
				button->onRelease = []() {
					Modules::Game->setCurrentScreen(Screens::OPTIONS);
					};
			}
		}
	}
}

bool MainMenu::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::Resized) {
		return UIScreen::handleEvent(event);
	}
	for (auto& element : elements) {
		if (std::shared_ptr<UIButton> button = std::dynamic_pointer_cast<UIButton>(element.second)) {
			if (!button->handleEvent(event)) {
				button->dropShadows(Colors::WHITE, Colors::GREY);
			}
		}
	}
	return true;
}
