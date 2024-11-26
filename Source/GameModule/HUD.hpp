#include "UISystem/UIScreen.hpp"

class HUD : public UIScreen
{
public:
	HUD(sf::RenderWindow* renderWindow, const std::string& hudFont, const std::string& pathToIniFile);

	void setTime(const std::string& newTime);

	void setScore(const std::string& newScore);

	void setLivesLeft(const std::string& newLivesLeft);
};