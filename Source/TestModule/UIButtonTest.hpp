#pragma once

#include "TestModule/TestBase.hpp"
#include "UISystem/UIButton.hpp"
#include <string>
#include <memory>
#include <UISystem/UIScreen.hpp>

class UIButtonTest : public TestBase
{
public:
	const std::string& getName() const override;
	void setup() override;
	void run() override;
	void update(float deltaTime, sf::RenderWindow* window) override;
	bool isComplete() const override;

private:
	std::shared_ptr<UIButton> button;
	bool completed = false;
	std::string Name = "UIButtonTest";
	UIScreen screen;
};
