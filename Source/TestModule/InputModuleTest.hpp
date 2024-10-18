#pragma once
#include "TestModule/TestBase.hpp"
#include "InputModule/InputModule.hpp"
#include "EventSystem/EventSystem.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

class InputModule;

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
	std::unique_ptr<InputModule> inputModule;
	int32_t passedTestsCount = 0;
	int32_t numberOfTests = 3;
	void buttonTest(bool state);
	void axis1DTest(float state);
	void axis2DTest(sf::Vector2f state);
};

