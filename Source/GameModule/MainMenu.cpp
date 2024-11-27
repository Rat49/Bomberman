#include "MainMenu.hpp"
#include "UISystem/UIFactory.hpp"
#include "UISystem/UIButton.hpp"
#include "Common/Logs.hpp"
#include "Screens.hpp"
#include "GameModule.hpp"

namespace
{
	const sf::Color& WHITE = sf::Color::White;
	const sf::Color& GREY = sf::Color(128, 128, 128);
	const sf::Color& YELLOW = sf::Color(247, 190, 57);
	const sf::Color& RED = sf::Color(173, 0, 16);
	const std::string& START = "START";
}

MainMenu::MainMenu(sf::RenderWindow* renderWindow, const std::string& font, const std::string& pathToIniFile) : UIScreen()
{
	setWindow(renderWindow);

	UIFactory::makeScreen(pathToIniFile, this, font);

	for (auto& element : elements) {
		if (std::shared_ptr<UIButton> button = std::dynamic_pointer_cast<UIButton>(element.second)) {
			button->onHover = [button]() {
				button->dropShadows(YELLOW, RED);
			};
			button->onClick = [button]() {
				button->dropShadows(RED, YELLOW);
			};
			if (element.first == START) {
				button->onRelease = []() {
					Modules::Game->setCurrentScreen(Screens::STAGE);
				};
			}

		}
	}
}

bool MainMenu::handleEvent(const sf::Event& event)
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
