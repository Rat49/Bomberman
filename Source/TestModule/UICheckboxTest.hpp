#pragma once
#include "TestModule/TestBase.hpp"
#include "UISystem/UICheckbox.hpp"
#include "UISystem/UILabel.hpp"
#include "UISystem/UIScreen.hpp"
#include <SFML/Graphics.hpp>

class UICheckboxTest : public TestBase
{
public:
    const std::string& getName() const override;
    void               setup() override;
    void               run() override;
    void               update(float deltaTime, sf::RenderWindow* window) override;
    bool               isComplete() const override;

private:
    const std::string           Name = "UICheckboxTest";
    std::shared_ptr<UICheckbox> checkBox;
    std::shared_ptr<UICheckbox> checkBox1;
    std::shared_ptr<UIScreen>   screen1;
};
