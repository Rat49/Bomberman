#pragma once

#include "TestModule/TestBase.hpp"
#include "UISystem/UIButton.hpp"
#include "UISystem/UILabel.hpp"
#include <UISystem/UIScreen.hpp>
#include <memory>
#include <string>

class UIButtonTest : public TestBase
{
public:
    const std::string& getName() const override;
    void               setup() override;
    void               run() override;
    void               update(float deltaTime, sf::RenderWindow* window) override;
    bool               isComplete() const override;

private:
    std::shared_ptr<UIButton> button;
    std::shared_ptr<UIButton> button2;
    std::shared_ptr<UIButton> button3;
    std::shared_ptr<UIButton> button4;

    std::shared_ptr<UILabel> label1;
    std::shared_ptr<UILabel> label2;
    std::shared_ptr<UILabel> label3;
    std::shared_ptr<UILabel> label4;

    std::shared_ptr<UIScreen> screen1;
    bool                      completed = false;
    std::string               Name      = "UIButtonTest";
    UIScreen                  screen;
};
