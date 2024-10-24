#pragma once
#include "TestModule/TestBase.hpp"
#include "EventSystem/EventSystem.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <tuple>

struct WindowCloseParams
{
	int32_t param1;
	float param2;
	std::string param3;
};

class WindowClosingTest : public TestBase
{
public:
	const std::string& getName() const override;
	void setup() override;
	void run() override;
	void update(float) override { }
	bool isComplete() const override;

private:
	const std::string Name = "WindowClosingTest";
	sf::RenderWindow window;
	bool windowClosed = false;
	int32_t windowCloseEventID = -1;
	FunctionHandle handle;

	void onWindowClosedEvent(int32_t param1, float param2, const std::string& param3);
};