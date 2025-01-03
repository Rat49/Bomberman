#include "UICheckboxTest.hpp"
#include "Common/Logs.hpp"
#include <chrono>
#include <thread>

const std::string& UICheckboxTest::getName() const
{
    return Name;
}

void UICheckboxTest::setup()
{
    LOG("UICheckboxTest: setup()");
    checkBox  = std::make_shared<UICheckbox>(40.f);
    checkBox1 = std::make_shared<UICheckbox>(50.f);
    sf::Vector2f pos(100.f, 100.f);
    checkBox->setPosition(pos);
    checkBox1->setPosition(pos + pos);
    checkBox1->setDefaultColorInsideRect(sf::Color::Black);
    checkBox1->setDefaultColorOutsideRect(sf::Color::Yellow);
    checkBox1->setHoverColorOutsideRect(sf::Color::Green);
    checkBox1->setFactor(0.5f);
    screen1 = std::make_shared<UIScreen>();
    screen1->addElement("CheckBox", checkBox);
    screen1->addElement("CheckBox1", checkBox1);

    checkBox1->onHover = []() { LOG("checkBox1 onHover event triggered!"); };
    checkBox1->onClick = []() { LOG("checkBox1 onClick triggered!"); };
}

void UICheckboxTest::run()
{
    LOG("UICheckboxTest: run()");
}

void UICheckboxTest::update(float, sf::RenderWindow* window)
{
    if (window && !screen1->getWindow())
    {
        screen1->setWindow(window);
    }
    sf::Event event;
    while (!checkBox->isChecked() || !checkBox1->isChecked())
    {
        window->clear();
        window->pollEvent(event);
        checkBox->handleEvent(event);
        checkBox1->handleEvent(event);
        screen1->draw(*window, sf::RenderStates::Default);
        window->display();
        if (event.type == sf::Event::Resized)
        {
            Modules::UI->setViewportSize((float)(screen1->getWindow()->getSize().x),
                                         (float)(screen1->getWindow()->getSize().y));
            screen1->handleEvent(event);
        }
    }
}

bool UICheckboxTest::isComplete() const
{
    return true;
}
