#pragma once
#include "TestModule/TestBase.hpp"
#include "InputModule/InputModule.hpp"
#include <SFML/Graphics.hpp>

class InputModuleTest : public TestBase
{
public:
	const std::string& getName() const override;
	void setup() override;
	void run() override;
	void update(float deltaTime, sf::RenderWindow*) override;
	bool isComplete() const override;

private:
	const std::string Name = "InputModuleTest";
	int32_t bindedFunctions = 0;
	int32_t numberOfFunctions = 3;
	void buttonTest(void* buttonState);
	void axis1DTest(void* axis1DState);
	void axis2DTest(void* axis2DState);
};

