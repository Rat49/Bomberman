#include "Options.hpp"
#include "Common/Modules.hpp"
#include "ConfigSystem/ConfigSystem.hpp"
#include "GameModule/GameModule.hpp"
#include "GameModule/MusicFactory.hpp"
#include "InputModule/InputModule.hpp"
#include "SoundSystem/SoundSystem.hpp"
#include "UIConstants.hpp"
#include "UISystem/UIButton.hpp"
#include "UISystem/UIFactory.hpp"
#include "UISystem/UIInputField.hpp"
#include "UISystem/UILabel.hpp"
#include "UISystem/UISlider.hpp"

namespace
{
const std::string AUDIO               = "AUDIO";
const std::string VIDEO               = "VIDEO";
const std::string KEYS                = "KEYS";
const std::string BACK                = "BACK";
const std::string MUSIC               = "MUSIC_SLIDER";
const std::string SOUNDS              = "SOUND_SLIDER";
const std::string RESOLUTION          = "RESOLUTION_SLIDER";
const std::string RESOLUTION_LABEL    = "SELECTED_RESOLUTION";
const std::string WINDOWED            = "WINDOWED";
const std::string FULLSCREEN          = "FULLSCREEN";
const std::string ELEMENT             = "element";
const std::string TYPE                = "type";
const std::string ARROW               = "ARROW";
const std::string INPUT_SECTION       = "inputSection";
const std::string PATH_SCREENS        = "../../Data/Config/optionsScreens.ini";
const std::string PATH_INPUT_BINDINGS = "../../Data/Config/optionsInputBindings.ini";
const std::string PATH_INPUT          = "../../Data/Config/input_config.ini";
} // namespace

Options::Options(sf::RenderWindow* renderWindow, const std::string& optionsFont, const std::string& pathToIniFile)
{
    setWindow(renderWindow);

    currentWindowSize = {renderWindow->getSize().x, renderWindow->getSize().y};

    UIFactory::makeScreen(pathToIniFile, this, optionsFont);

    readScreens();

    for (auto& element : elements)
    {
        if (std::shared_ptr<UIButton> button = std::dynamic_pointer_cast<UIButton>(element.second))
        {
            button->onHover = [button]() { button->dropShadows(Colors::YELLOW, Colors::RED); };
            button->onClick = [button]() { button->dropShadows(Colors::RED, Colors::YELLOW); };

            if (element.first == BACK)
            {
                button->onRelease = [this]()
                {
                    hideScreen();
                    if (Modules::Game->getIsPaused())
                    {
                        Modules::Game->setCurrentScreen(Screens::LEVEL);
                        Modules::Sounds->playMusic(static_cast<int32_t>(AllMusic::Background));
                    }
                    else
                    {
                        Modules::Game->setCurrentScreen(Screens::MAIN_MENU);
                        Modules::Sounds->playMusic(static_cast<int32_t>(AllMusic::Title));
                    }
                };
            }
            else if (element.first == FULLSCREEN)
            {
                button->onRelease = [this, element]()
                {
                    if (!fullscreen)
                    {
                        // creating window with sf::Style::Fullscreen
                        window->create(sf::VideoMode(currentWindowSize.first, currentWindowSize.second),
                                       Modules::Game->getGameTitle(),
                                       sf::Style::Fullscreen);

                        Modules::Game->handleResize((float)(currentWindowSize.first), (float)(currentWindowSize.second));

                        // placing arrow animation
                        auto arrowAnimation = getAnimation(ARROW);
                        arrowAnimation->setPosition(
                            sf::Vector2f(arrowAnimation->getPosition().x, element.second->getPosition().y));

                        fullscreen = true;
                    }
                };
            }
            else if (element.first == WINDOWED)
            {
                button->onRelease = [this, element]()
                {
                    if (fullscreen)
                    {
                        // creating window with sf::Style::Default
                        window->create(sf::VideoMode(currentWindowSize.first, currentWindowSize.second, sf::Style::Close),
                                       Modules::Game->getGameTitle(),
                                       sf::Style::Close);

                        Modules::Game->handleResize((float)(currentWindowSize.first), (float)(currentWindowSize.second));

                        // placing arrow animation
                        auto arrowAnimation = getAnimation(ARROW);
                        arrowAnimation->setPosition(
                            sf::Vector2f(arrowAnimation->getPosition().x, element.second->getPosition().y));

                        fullscreen = false;
                    }
                };
            }
            else
            {
                button->onRelease = [this, element]() { showScreen(element.first); };
            }
        }
        else if (std::shared_ptr<UISlider> slider = std::dynamic_pointer_cast<UISlider>(element.second))
        {
            if (element.first == MUSIC)
            {
                slider->onValueChanged = [](float value) { Modules::Sounds->setMusicVolume(value); };
            }
            else if (element.first == SOUNDS)
            {
                slider->onValueChanged = [](float value) { Modules::Sounds->setSoundsVolume(value); };
            }
            else if (element.first == RESOLUTION)
            {
                setResolutionLabel(-1.f);

                slider->onValueChanged = [this](float value) { setResolutionLabel(value); };

                slider->onReleased = [this]()
                {
                    if (changedWindowSize != currentWindowSize)
                    {
                        currentWindowSize = changedWindowSize;

                        if (fullscreen)
                            window->create(sf::VideoMode(currentWindowSize.first, currentWindowSize.second),
                                           Modules::Game->getGameTitle(),
                                           sf::Style::Fullscreen);
                        else
                            window->create(sf::VideoMode(currentWindowSize.first, currentWindowSize.second),
                                           Modules::Game->getGameTitle(),
                                           sf::Style::Close);

                        Modules::Game->handleResize((float)(window->getSize().x), (float)(window->getSize().y));
                    }
                };
            }
        }
    }
}

bool Options::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::Resized)
    {
        return UIScreen::handleEvent(event);
    }
    for (auto& element : elements)
    {
        if (std::shared_ptr<UIButton> button = std::dynamic_pointer_cast<UIButton>(element.second))
        {
            if (button->isVisible() && !button->handleEvent(event))
            {
                button->dropShadows(Colors::WHITE, Colors::GREY);
            }
        }
        else if (std::shared_ptr<UISlider> slider = std::dynamic_pointer_cast<UISlider>(element.second))
        {
            if (slider->isVisible())
                slider->handleEvent(event);
        }
        else if (std::shared_ptr<UIInputField> inputField = std::dynamic_pointer_cast<UIInputField>(element.second))
        {
            if (inputField->isVisible())
            {
                remapKey(inputField, event, element.first);
            }
        }
    }
    return true;
}

void Options::readScreens()
{
    Modules::Config->addFile(PATH_SCREENS);
    Modules::Config->addFile(PATH_INPUT_BINDINGS);

    const auto& optionScreeens = Modules::Config->getFile(PATH_SCREENS);

    // For getting key bindings
    const auto& optionInputBindings = Modules::Config->getFile(PATH_INPUT_BINDINGS);
    const auto& input               = Modules::Config->getFile(PATH_INPUT);

    const auto& optionButtons = optionScreeens.getAllSections();

    int32_t i;
    for (auto& button : optionButtons)
    {
        i                        = 1;
        const auto& optionScreen = optionScreeens.getSection(button);

        // Reading file
        while (true)
        {
            const auto& element = ELEMENT + std::to_string(i);
            if (!optionScreen.isValuePresent(element))
                break;

            // value is UIElement
            const auto& value = optionScreen.getValue(element).getString();
            screens[button].push_back(value);

            // checking if that UIElement exists
            if (auto elem = getElement(value))
            {

                // by default all elements that are in this file should be hidden
                elem->setVisible(false);

                // check if element is inside bindings file
                if (optionInputBindings.isSectionPresent(value))
                {

                    const auto& binding        = optionInputBindings.getSection(value);
                    const auto& bindingType    = binding.getValue(TYPE).getString();
                    const auto& bindingSection = binding.getValue(INPUT_SECTION).getString();

                    // read binding from input config file
                    const auto& text = input.getSection(bindingSection).getValue(bindingType).getString();

                    registeredKeys.insert(text);

                    // setting text for that UIInputField
                    auto inputField = std::dynamic_pointer_cast<UIInputField>(elem);
                    inputField->setText(text);
                    inputField->setInitialText(text);
                }
            }
            if (auto animation = getAnimation(value))
                animation->Stop();
            i++;
        }
    }
}

void Options::showScreen(const std::string& name)
{
    if (!currentScreen.empty() || currentScreen == name)
    {
        for (auto& elementName : screens[currentScreen])
        {
            if (auto element = getElement(elementName))
            {
                element->setVisible(false);
            }
            if (auto animation = getAnimation(elementName))
            {
                animation->Stop();
            }
        }
    }
    if (currentScreen == name)
    {
        currentScreen.clear();
        return;
    }

    currentScreen = name;

    for (auto& elementName : screens[currentScreen])
    {
        if (auto element = getElement(elementName))
        {
            element->setVisible(true);
        }
        if (auto animation = getAnimation(elementName))
        {
            animation->Play();
        }
    }
}

void Options::remapKey(std::shared_ptr<UIInputField> inputField, const sf::Event& event, const std::string& elementName)
{
    bool previousVersion = inputField->getText().empty();
    if (inputField->handleEvent(event) && previousVersion)
    {
        if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::Key::Up:
                    inputField->setText("Up");
                    break;
                case sf::Keyboard::Key::Down:
                    inputField->setText("Down");
                    break;
                case sf::Keyboard::Key::Left:
                    inputField->setText("Left");
                    break;
                case sf::Keyboard::Key::Right:
                    inputField->setText("Right");
                    break;
            }
        }
        if (!inputField->getText().empty())
        {

            auto&       binding        = Modules::Config->getFile(PATH_INPUT_BINDINGS).getSection(elementName);
            const auto& bindingType    = binding.getValue(TYPE).getString();
            const auto& bindingSection = binding.getValue(INPUT_SECTION).getString();

            std::string currentText = inputField->getText();
            if (currentText == " ")
                inputField->setText("Space");
            else if (currentText.length() == 1)
            {
                std::transform(currentText.begin(), currentText.end(), currentText.begin(), ::toupper);
                inputField->setText(currentText);
            }

            if (checkDuplicates(inputField->getText(), inputField->getInitialText()))
            {
                //update binding

                if (binding.isValuePresent("axis"))
                {
                    Modules::Input->updateBinding(bindingSection,
                                                  bindingType,
                                                  inputField->getText(),
                                                  binding.getValue("axis").getString());
                }
                else
                {
                    Modules::Input->updateBinding(bindingSection, bindingType, inputField->getText());
                }

                inputField->setInitialText(inputField->getText());
            }
            else
            {
                inputField->setText(inputField->getInitialText());
            }
            inputField->setWritable(false);
            inputField->setHasPlaceholder(true);
        }
    }
}

bool Options::checkDuplicates(const std::string& newKey, const std::string& oldKey)
{
    if (registeredKeys.count(newKey))
    {
        LOG("Key is already mapped!");
        return false;
    }
    registeredKeys.erase(oldKey);
    registeredKeys.insert(newKey);
    return true;
}

// Set new value for selected resolution
void Options::setResolutionLabel(float value)
{
    auto allModes = sf::VideoMode::getFullscreenModes();

    int32_t index = 0;

    if (value == -1.f)
    {

        // for finding current resolution, and setting initial slider value
        auto it = std::find(allModes.begin(), allModes.end(), sf::VideoMode(currentWindowSize.first, currentWindowSize.second));

        if (it != allModes.end())
        {
            index = (int32_t)std::distance(allModes.begin(), it);
        }
    }
    else if (value == 0.f)
    {
        index = (int32_t)(allModes.size() - 1);
    }
    else
    {
        // getting resolution based on slider value
        index = (int32_t)((100.f - value) * allModes.size() / 100.f);
    }
    sf::VideoMode newVideoMode = sf::VideoMode::getFullscreenModes()[index];

    changedWindowSize = {newVideoMode.width, newVideoMode.height};

    auto scoreLabel = std::dynamic_pointer_cast<UILabel>(getElement(RESOLUTION_LABEL));
    if (scoreLabel)
    {
        scoreLabel->setText(std::to_string(newVideoMode.width) + "x" + std::to_string(newVideoMode.height));

        // setting slider value
        if (value == -1.f)
        {
            std::dynamic_pointer_cast<UISlider>(getElement(RESOLUTION))->setValue(100.f - 100.f * index / allModes.size());
        }
    }
}

void Options::hideScreen()
{
    if (!currentScreen.empty())
    {
        for (auto& elementName : screens[currentScreen])
        {
            if (auto element = getElement(elementName))
            {
                element->setVisible(false);
            }
            if (auto animation = getAnimation(elementName))
            {
                animation->Stop();
            }
        }
        currentScreen.clear();
    }
}
