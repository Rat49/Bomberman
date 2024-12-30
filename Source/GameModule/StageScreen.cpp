#include "StageScreen.hpp"
#include "UISystem/UIFactory.hpp"
#include "UISystem/UILabel.hpp"

namespace
{
	const std::string& STAGE = "STAGE";
}

StageScreen::StageScreen(sf::RenderWindow* renderWindow, const std::string& hudFont, const std::string& pathToIniFile) : UIScreen()
{
	setWindow(renderWindow);

	UIFactory::makeScreen(pathToIniFile, this, hudFont);
}

void StageScreen::setStage(int32_t newStage)
{
	auto stageLabel = std::dynamic_pointer_cast<UILabel>(getElement(STAGE));
	if (stageLabel)
        stageLabel->setText(STAGE + " " + std::to_string(newStage));
}
