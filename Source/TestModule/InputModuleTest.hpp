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
	void update(float deltaTime) override;
	bool isComplete() const override;

private:
	const std::string Name = "InputModuleTest";
	int32_t bindedFunctions = 0;
	int32_t numberOfFunctions = 3;
	void buttonTest(bool state);
	void axis1DTest(float state);
	void axis2DTest(sf::Vector2f state);
};

