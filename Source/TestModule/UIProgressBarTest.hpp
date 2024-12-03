#pragma once

#include "TestModule/TestBase.hpp"
#include "UISystem/UIProgressBar.hpp"
#include "UISystem/UISlider.hpp"
#include <UISystem/UIScreen.hpp>
#include <string>
#include <memory>

class UIProgressBarTest : public TestBase
{
public:
	const std::string& getName() const override;
	void setup() override;
	void run() override;
	void update(float deltaTime, sf::RenderWindow*) override;
	bool isComplete() const override;

private:
	std::shared_ptr<UIProgressBar> progressBar;
	std::shared_ptr<UISlider> slider;

	std::shared_ptr<UIScreen> screen;
	bool completed = false;
	std::string Name = "UIProgressBarTest";
};
