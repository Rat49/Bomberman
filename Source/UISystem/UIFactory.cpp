#include "UIFactory.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "Common/Modules.hpp"
#include "UIScreen.hpp"
#include "UILabel.hpp"

namespace
{
	const std::string& TYPE = "type";
	const std::string& NAME = "name";
	const std::string& VALUE = "value";
	const std::string& LABEL_COLOR = "labelColor";
	const std::string& SHADOW_COLOR = "shadowColor";
	const std::string& OFFSET = "offset";
	const std::string& UILABEl = "UILabel";
}

void UIFactory::makeScreen(const std::string& path, UIScreen* screen, const std::string& screenFont)
{
	const ConfigFile& configFile = Modules::Config->getFile(path);

	const auto& sections = configFile.getAllSections();

	for (const auto& sectionName : sections)
	{
		if (configFile.getSection(sectionName).areValuesPresent({ TYPE }))
		{
			// Take type of UI element
			const ConfigSection& element = configFile.getSection(sectionName);
			const std::string& elementType = configFile.getSection(sectionName).getValue(TYPE).getString();
			
			if (elementType == UILABEl)
			{
				makeUILabel(screen, screenFont, element);
			}
			// Add UI Button here
		}
	}
}

void UIFactory::makeUILabel(UIScreen* screen, const std::string& screenFont, const ConfigSection& element)
{
	auto& font = screen->getFont(screenFont);

	int32_t width = screen->getWindow()->getSize().x;
	int32_t heigth = screen->getWindow()->getSize().y;

	auto characterSize = static_cast<unsigned int>(0.0375 * width);

	// Check if necessary values are present
	if (element.areValuesPresent({ NAME, VALUE, OFFSET }))
	{
		auto& elementName = element.getValue(NAME).getString();
		auto& elementValue = element.getValue(VALUE).getString();
		float elementOffset = element.getValue(OFFSET).getFloat();

		auto myLabel = std::make_shared<UILabel>(elementValue, font, characterSize);

		myLabel->setPosition(sf::Vector2f(elementOffset * width, 0.017f * heigth));

		// Check if label has shadow
		if (element.areValuesPresent({ LABEL_COLOR, SHADOW_COLOR }))
		{
			auto& labelColor = element.getValue(LABEL_COLOR).getString();
			auto& shadowColor = element.getValue(SHADOW_COLOR).getString();

			myLabel->dropShadows(sf::Color(std::stoul(labelColor, nullptr, 16)),
				sf::Color(std::stoul(shadowColor, nullptr, 16)));
		}

		screen->addElement(elementName, myLabel);
	}
}
