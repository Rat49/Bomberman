#include "Options.hpp"
#include "UISystem/UIFactory.hpp"
#include "UISystem/UIButton.hpp"
#include "Common/Modules.hpp"
#include "GameModule/GameModule.hpp"

namespace
{
	const sf::Color& WHITE = sf::Color::White;
	const sf::Color& GREY = sf::Color(128, 128, 128);
	const sf::Color& YELLOW = sf::Color(247, 190, 57);
	const sf::Color& RED = sf::Color(173, 0, 16);
	const std::string& AUDIO = "AUDIO";
	const std::string& VIDEO = "VIDEO";
	const std::string& KEYS = "KEYS";
	const std::string& BACK = "BACK";
}

Options::Options(sf::RenderWindow* renderWindow, const std::string& optionsFont, const std::string& pathToIniFile)
{
	setWindow(renderWindow);

	UIFactory::makeScreen(pathToIniFile, this, optionsFont);

	for (auto& element : elements) {
		if (std::shared_ptr<UIButton> button = std::dynamic_pointer_cast<UIButton>(element.second)) {
			button->onHover = [button]() {
				button->dropShadows(YELLOW, RED);
				};
			button->onClick = [button]() {
				button->dropShadows(RED, YELLOW);
				};
			if (element.first == AUDIO) {
				button->onRelease = [this]() {
					showAudio();
					//Modules::Game->setCurrentScreen(Screens::STAGE);
					};
			}
			else if (element.first == VIDEO) {
				button->onRelease = []() {
					//Modules::Game->setCurrentScreen(Screens::LEADERBOARD);
					};
			}
			else if (element.first == KEYS) {
				button->onRelease = []() {
					//Modules::Game->setCurrentScreen(Screens::LEADERBOARD);
					};
			}
			else if (element.first == BACK) {
				button->onRelease = []() {
					//if(Modules::Game->getIsPaused)
					//	Modules::Game->setCurrentScreen(Screens::LEVEL);
					//else
					Modules::Game->setCurrentScreen(Screens::MAIN_MENU);
					};
			}
		}
	}
}

bool Options::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::Resized) {
		return UIScreen::handleEvent(event);
	}
	for (auto& element : elements) {
		if (std::shared_ptr<UIButton> button = std::dynamic_pointer_cast<UIButton>(element.second)) {
			if (button->isVisible() && !button->handleEvent(event)) {
				button->dropShadows(WHITE, GREY);
			}
		}
	}
	return true;
}

void Options::showAudio()
{

}
