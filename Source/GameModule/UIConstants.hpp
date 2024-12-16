#pragma once

enum class Screens {
	MAIN_MENU, STAGE, LEVEL, LEADERBOARD, PAUSE_MENU, OPTIONS, GAME_OVER
};

namespace Colors{
	const sf::Color WHITE = sf::Color(255, 255, 255);
	const sf::Color GREY = sf::Color(128, 128, 128);
	const sf::Color YELLOW = sf::Color(247, 190, 57);
	const sf::Color RED = sf::Color(173, 0, 16);
	const sf::Color LIGHT_GREY = sf::Color(189, 190, 189);
};

namespace Buttons {
	const std::string RESUME = "RESUME";
	const std::string MENU = "MENU";
	const std::string LEADERBOARD = "LEADERBOARD";
	const std::string OPTIONS = "OPTIONS";
	const std::string START = "START";
}