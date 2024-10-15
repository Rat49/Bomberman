#pragma once
#include "TestModule/TestBase.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class InputModule;

class InputModuleTest : public TestBase
{
public:
	const std::string& getName() const override;
	void setup() override;
	void run() override;
	void update(float deltaTime) override { deltaTime = 0.0f; }
	bool isComplete() const override;

private:
	const std::string Name = "InputModuleTest";
	InputModule* inputModule;
	void sample_function();
};

