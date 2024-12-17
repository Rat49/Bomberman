#include "UIFactory.hpp"
#include "Common/Modules.hpp"
#include "UIScreen.hpp"
#include "UILabel.hpp"
#include "UIButton.hpp"
#include "UISlider.hpp"
#include "UIInputField.hpp"
#include "SpriteModule/SpriteModule.hpp"
#include "ConfigSystem/ConfigSystem.hpp"

namespace
{
	const std::string TYPE = "type";
	const std::string NAME = "name";
	const std::string VALUE = "value";
	const std::string TEXT_COLOR = "textColor";
	const std::string SHADOW_COLOR = "shadowColor";
	const std::string DEFAULT_COLOR = "defaultColor";
	const std::string HOVER_COLOR = "hoverColor";
	const std::string PRESSED_COLOR = "pressedColor";
	const std::string FIELD_COLOR = "fieldColor";
	const std::string WIDTH_OFFSET = "widthOffset";
	const std::string HEIGHT_OFFSET = "heightOffset";
	const std::string RECTANGLE_WIDTH = "rectangleWidth";
	const std::string BAR_VALUE = "barValue";
	const std::string REICTANGLE_HEIGHT = "rectangleHeight";
	const std::string BACKGROUND_COLOR = "backgroundColor";
	const std::string BAR_COLOR = "barColor";
	const std::string KNOB_COLOR = "knobColor";
	const std::string UISCREEN = "UIScreen";
	const std::string UILABEl = "UILabel";
	const std::string ANIMATION = "Animation";
	const std::string UIBUTTON = "UIButton";
	const std::string UISLIDER = "UISlider";
	const std::string UIINPUTFIELD = "UIInputField";
	const std::string PATH = "path";
	const float FACTOR_WIDTH = 0.0375f; // factor for text size, based on width (30/800)
	const std::string FACTOR_SIZE = "factorSize";
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
			auto& element = configFile.getSection(sectionName);
			auto& elementType = element.getValue(TYPE).getString();
			
			if (elementType == UISCREEN) {
				setUIScreen(screen, element);
			}
			else if (elementType == UILABEl) {
				makeUILabel(screen, screenFont, element);
			}
			else if (elementType == ANIMATION) {
				makeAnimation(screen, element);
			}
			else if (elementType == UIBUTTON) {
				makeUIButton(screen, screenFont, element);
			}
			else if (elementType == UISLIDER) {
				makeUISlider(screen, element);
			}
			else if (elementType == UIINPUTFIELD) {
				makeUIInputField(screen, screenFont, element);
			}
		}
	}
}

void UIFactory::setUIScreen(UIScreen* screen, const ConfigSection& element)
{
    if (element.isValuePresent(BACKGROUND_COLOR))
    {
        auto& backgroundColor = element.getValue(BACKGROUND_COLOR).getString();
        screen->setBackgroundColor(sf::Color(std::stoul(backgroundColor, nullptr, 16)));
    }
    if (element.areValuesPresent({WIDTH_OFFSET, HEIGHT_OFFSET, REICTANGLE_HEIGHT, REICTANGLE_HEIGHT})) {
        int32_t width  = screen->getWindow()->getSize().x;
        int32_t height = screen->getWindow()->getSize().y;

        float elementWidthOffset  = element.getValue(WIDTH_OFFSET).getFloat();
        float elementHeightOffset = element.getValue(HEIGHT_OFFSET).getFloat();
        float elementWidth        = element.getValue(RECTANGLE_WIDTH).getFloat();
        float elementHeight       = element.getValue(REICTANGLE_HEIGHT).getFloat();

        screen->setBackground(elementWidthOffset * width, elementHeightOffset * height, elementWidth, elementHeight);
    }
}

void UIFactory::makeUILabel(UIScreen* screen, const std::string& screenFont, const ConfigSection& element)
{
    auto& font = screen->getFont(screenFont);

    int32_t width  = screen->getWindow()->getSize().x;
    int32_t height = screen->getWindow()->getSize().y;

    float factorSize = 1.0f;
    if (element.isValuePresent(FACTOR_SIZE)) {
        factorSize = element.getValue(FACTOR_SIZE).getFloat();
    }
    auto characterSize = static_cast<unsigned int>(FACTOR_WIDTH * width * factorSize);

    // Check if necessary values are present
    if (element.areValuesPresent({NAME, VALUE, WIDTH_OFFSET, HEIGHT_OFFSET}))
    {
        auto& elementName         = element.getValue(NAME).getString();
        auto& elementValue        = element.getValue(VALUE).getString();
        float elementWidthOffset  = element.getValue(WIDTH_OFFSET).getFloat();
        float elementHeightOffset = element.getValue(HEIGHT_OFFSET).getFloat();

        auto myLabel = std::make_shared<UILabel>(elementValue, font, characterSize);

        myLabel->setPosition(sf::Vector2f(elementWidthOffset * width, elementHeightOffset * height));

        // Check if label has shadow
        if (element.areValuesPresent({TEXT_COLOR, SHADOW_COLOR}))
        {
            auto& labelColor  = element.getValue(TEXT_COLOR).getString();
            auto& shadowColor = element.getValue(SHADOW_COLOR).getString();

            myLabel->dropShadows(sf::Color(std::stoul(labelColor, nullptr, 16)),
                                 sf::Color(std::stoul(shadowColor, nullptr, 16)));
        }

        screen->addElement(elementName, myLabel);
    }
}

void UIFactory::makeAnimation(UIScreen* screen, const ConfigSection& element)
{
    if (element.areValuesPresent({PATH, NAME, WIDTH_OFFSET, HEIGHT_OFFSET})) {
        auto&   animationPath = element.getValue(PATH).getString();
        auto&   animationName = element.getValue(NAME).getString();
        int32_t animationId   = Modules::Sprite->createAnimation(animationPath);
        float   x             = element.getValue(WIDTH_OFFSET).getFloat();
        float   y             = element.getValue(HEIGHT_OFFSET).getFloat();

        if (const auto& animation = Modules::Sprite->getAnimation(animationId)) {
            animation->Play();

            auto screenSize = screen->getWindow()->getSize();
            animation->setPosition(sf::Vector2f(screenSize.x * x, screenSize.y * y));

            screen->addAnimation(animationName, animation);
        }
    }
}

void UIFactory::makeUIButton(UIScreen* screen, const std::string& screenFont, const ConfigSection& element)
{
    auto& font = screen->getFont(screenFont);

    int32_t width  = screen->getWindow()->getSize().x;
    int32_t height = screen->getWindow()->getSize().y;

    auto characterSize = static_cast<unsigned int>(FACTOR_WIDTH * width);

    // Check if necessary values are present
    if (element.areValuesPresent({NAME, VALUE, WIDTH_OFFSET, HEIGHT_OFFSET, RECTANGLE_WIDTH, REICTANGLE_HEIGHT}))
    {
        auto& elementName         = element.getValue(NAME).getString();
        auto& elementValue        = element.getValue(VALUE).getString();
        float elementWidthOffset  = element.getValue(WIDTH_OFFSET).getFloat();
        float elementHeightOffset = element.getValue(HEIGHT_OFFSET).getFloat();
        float elementWidth        = element.getValue(RECTANGLE_WIDTH).getFloat();
        float elementHeight       = element.getValue(REICTANGLE_HEIGHT).getFloat();

        auto myButton = std::make_shared<UIButton>(elementValue, font, characterSize, sf::Vector2f(elementWidth, elementHeight));

        myButton->setPosition(sf::Vector2f(elementWidthOffset * width, elementHeightOffset * height));

        // Check if button has shadow
        if (element.areValuesPresent({TEXT_COLOR, SHADOW_COLOR})) {
            auto& textColor   = element.getValue(TEXT_COLOR).getString();
            auto& shadowColor = element.getValue(SHADOW_COLOR).getString();

            myButton->dropShadows(sf::Color(std::stoul(textColor, nullptr, 16)),
                                  sf::Color(std::stoul(shadowColor, nullptr, 16)));
        }
        bool hasSomeColor = false;
        // Check if button has defined default background color (not Black)
        if (element.isValuePresent(DEFAULT_COLOR)) {
            hasSomeColor       = true;
            auto& defaultColor = element.getValue(DEFAULT_COLOR).getString();
            myButton->setDefaultColor(sf::Color(std::stoul(defaultColor, nullptr, 16)));
        }

        // Check if button has defined hover background color (not Black)
        if (element.isValuePresent(HOVER_COLOR)) {
            auto& buttonColor = element.getValue(HOVER_COLOR).getString();
            myButton->setHoverColor(sf::Color(std::stoul(buttonColor, nullptr, 16)));
        }

        // Check if button has defined on pressed background color (not Black)
        if (element.isValuePresent(PRESSED_COLOR)) {
            auto& buttonColor = element.getValue(PRESSED_COLOR).getString();
            myButton->setPressedColor(sf::Color(std::stoul(buttonColor, nullptr, 16)));
        }

        screen->addElement(elementName, myButton);
    }
}

void UIFactory::makeUISlider(UIScreen* screen, const ConfigSection& element)
{

	int32_t width = screen->getWindow()->getSize().x;
	int32_t height = screen->getWindow()->getSize().y;

	// Check if necessary values are present
	if (element.areValuesPresent({ NAME, WIDTH_OFFSET, HEIGHT_OFFSET, RECTANGLE_WIDTH, REICTANGLE_HEIGHT, BAR_VALUE}))
	{
		auto& elementName = element.getValue(NAME).getString();
		float elementWidthOffset = element.getValue(WIDTH_OFFSET).getFloat();
		float elementHeightOffset = element.getValue(HEIGHT_OFFSET).getFloat();
		float elementWidth = element.getValue(RECTANGLE_WIDTH).getFloat();
		float elementHeight = element.getValue(REICTANGLE_HEIGHT).getFloat();

		float bar_value = element.getValue(BAR_VALUE).getFloat();

		auto mySlider = std::make_shared<UISlider>(sf::Vector2f(elementWidth, elementHeight));
		mySlider->setValue(bar_value);
		mySlider->setPosition(sf::Vector2f(elementWidthOffset * width, elementHeightOffset * height));

		if (element.areValuesPresent({ BAR_COLOR, KNOB_COLOR })) {
			auto& barColor = element.getValue(BAR_COLOR).getString();
			auto& knobColor = element.getValue(KNOB_COLOR).getString();
			mySlider->setBarColor(sf::Color(std::stoul(barColor, nullptr, 16)));
			mySlider->setKnobColor(sf::Color(std::stoul(knobColor, nullptr, 16)));
		}
		
		
		screen->addElement(elementName, mySlider);
	}
}

void UIFactory::makeUIInputField(UIScreen* screen, const std::string& screenFont, const ConfigSection& element)
{
	auto& font = screen->getFont(screenFont);

	int32_t width = screen->getWindow()->getSize().x;
	int32_t height = screen->getWindow()->getSize().y;

	float factorSize = 1.0f;
	if (element.isValuePresent(FACTOR_SIZE)) {
		factorSize = element.getValue(FACTOR_SIZE).getFloat();
	}
	auto characterSize = static_cast<unsigned int>(FACTOR_WIDTH * width * factorSize);

	// Check if necessary values are present
	if (element.areValuesPresent({ NAME, WIDTH_OFFSET, HEIGHT_OFFSET, RECTANGLE_WIDTH, REICTANGLE_HEIGHT }))
	{
		auto& elementName = element.getValue(NAME).getString();
		float elementWidthOffset = element.getValue(WIDTH_OFFSET).getFloat();
		float elementHeightOffset = element.getValue(HEIGHT_OFFSET).getFloat();
		float elementWidth = element.getValue(RECTANGLE_WIDTH).getFloat();
		float elementHeight = element.getValue(REICTANGLE_HEIGHT).getFloat();

		auto myInputField = std::make_shared<UIInputField>(font, characterSize, sf::Vector2f(elementWidth, elementHeight));
		myInputField->setPosition(sf::Vector2f(elementWidthOffset * width, elementHeightOffset * height));

		if (element.areValuesPresent({ TEXT_COLOR, FIELD_COLOR })) {
			auto& textColor = element.getValue(TEXT_COLOR).getString();
			auto& fieldColor = element.getValue(FIELD_COLOR).getString();
			myInputField->setColor(sf::Color(std::stoul(fieldColor, nullptr, 16)), sf::Color(std::stoul(textColor, nullptr, 16)));
		}
		screen->addElement(elementName, myInputField);
	}
}
