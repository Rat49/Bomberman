#pragma once
#include "TestModule/TestBase.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class WindowClosingTest : public TestBase
{
public:
	const std::string& getName() const override;
	void setup() override;
	void run() override;
	void update(float deltaTime) override { deltaTime = 0.0f; }
	bool isComplete() const override;

private:
	const std::string Name = "WindowClosingTest";
	sf::RenderWindow window;
	bool windowClosed = false;
	int32_t windowCloseEventID = -1;
	void onWindowClosedEvent();
};
