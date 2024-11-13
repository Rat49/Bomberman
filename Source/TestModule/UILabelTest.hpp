#pragma once

#include "TestModule/TestBase.hpp"
#include "UISystem/UILabel.hpp"
#include <string>
#include <memory>
#include <UISystem/UIScreen.hpp>

class UILabelTest : public TestBase
{
public:
	const std::string& getName() const override;
	void setup() override;
	void run() override;
	void update(float deltaTime, sf::RenderWindow* window) override;
	bool isComplete() const override;

private:
	std::shared_ptr<UILabel> label;
	bool completed = false;
	std::string Name = "UILabelTest";
	UIScreen screen;
};
