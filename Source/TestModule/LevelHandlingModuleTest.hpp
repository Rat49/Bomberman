#pragma once

#include "TestBase.hpp"

class LevelHandlingModuleTest : public TestBase
{
public:
	const std::string& getName() const override;
	void setup() override;
	void run() override;
	void update(float, sf::RenderWindow* window) override;
	bool isComplete() const override;

private:
	const std::string m_name = "LevelHandlingTest";

};

