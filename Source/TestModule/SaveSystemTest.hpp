#pragma once
#include "TestModule/TestBase.hpp"

class SaveSystemTest : public TestBase
{
public:

	const std::string& getName() const override;

	void setup() override;

	void run() override;

	void update(float deltaTime, sf::RenderWindow* window) override;

	bool isComplete() const override;

private:

	const std::string m_name = "SaveSystemTest";

	bool m_isComplete;
};

