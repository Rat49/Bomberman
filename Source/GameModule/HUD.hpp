#include "UISystem/UIScreen.hpp"

class HUD : public UIScreen
{
public:
	HUD(sf::RenderWindow* renderWindow, const std::string& hudFont);

	void setTime(const std::string& newTime);

	void setScore(const std::string& newScore);

	void setLivesLeft(const std::string& newLivesLeft);
};