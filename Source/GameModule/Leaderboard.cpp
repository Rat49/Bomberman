#include "Leaderboard.hpp"
#include "UISystem/UIFactory.hpp"
#include "Common/Modules.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "UISystem/UILabel.hpp"
#include "UISystem/UIButton.hpp"
#include "GameModule/GameModule.hpp"
#include "Common/Logs.hpp"

namespace
{
	const std::string& PATH_LEARDERBOARD = "../../Data/Config/leaderboardResults.ini";
	const std::string& LEARDERBOARD = "LEARDERBOARD";
	const std::string& MENU = "MENU";
	const std::string& PLAYER = "Player";
	const std::string& NAME = "Name";
	const std::string& VALUE = "Value";

	const sf::Color& WHITE = sf::Color::White;
	const sf::Color& GREY = sf::Color(128, 128, 128);
	const sf::Color& YELLOW = sf::Color(247, 190, 57);
	const sf::Color& RED = sf::Color(173, 0, 16);

}

Leaderboard::Leaderboard(sf::RenderWindow* renderWindow, const std::string& hudFont, const std::string& pathToIniFile) : UIScreen()
{
	setWindow(renderWindow);

	UIFactory::makeScreen(pathToIniFile, this, hudFont);

	readLeaderboard();

	std::shared_ptr<UIButton> menuButton = std::dynamic_pointer_cast<UIButton>(getElement(MENU));

	menuButton->onHover = [menuButton]() {
		menuButton->dropShadows(YELLOW, RED);
		};
	menuButton->onClick = [menuButton]() {
		menuButton->dropShadows(RED, YELLOW);
		};
	menuButton->onRelease = []() {
		Modules::Game->setCurrentScreen(Screens::MAIN_MENU);
		};
}

void Leaderboard::readLeaderboard()
{
	Modules::Config->addFile(PATH_LEARDERBOARD);

	auto& leaderboardResults = Modules::Config->getFile(PATH_LEARDERBOARD);

	int32_t i = 1;
	while (i <= 5) {
		std::string sectionName = PLAYER + std::to_string(i);
		if (!leaderboardResults.isSectionPresent(sectionName)) {
			LOG("Missing player/s section in leaderboard results");
			break;
		}

		auto& player = leaderboardResults.getSection(sectionName);
		if (player.areValuesPresent({ NAME, VALUE })) {
			auto& playerName = player.getValue(NAME).getString();
			auto& playerResult = player.getValue(VALUE).getString();

			if (!playerName.empty())
			{
				// Setting name and result for that player
				(std::dynamic_pointer_cast<UILabel>(elements[sectionName]))->setText(playerName);
				sectionName += VALUE;
				(std::dynamic_pointer_cast<UILabel>(elements[sectionName]))->setText(playerResult);
			}
			else
			{
				// Setting for labels to not be visible as well as animation for that player
				(std::dynamic_pointer_cast<UILabel>(elements[sectionName]))->setVisible(false);
				if (animations.count(sectionName))
					animations[sectionName]->Stop();
				sectionName += VALUE;
				(std::dynamic_pointer_cast<UILabel>(elements[sectionName]))->setVisible(false);
			}
		}
		i++;
	}
}

bool Leaderboard::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::Resized) {
		return UIScreen::handleEvent(event);
	}
	std::shared_ptr<UIButton> menuButton = std::dynamic_pointer_cast<UIButton>(getElement(MENU));
	if (!menuButton->handleEvent(event)) {
		menuButton->dropShadows(WHITE, GREY);
	}
	return true;
}
