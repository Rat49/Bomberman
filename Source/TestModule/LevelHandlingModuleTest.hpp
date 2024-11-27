#pragma once

#include "TestBase.hpp"
#include "SFML/Graphics/View.hpp"

class LevelHandlingModuleTest : public TestBase
{
public:

	const std::string& getName() const override;

	void setup() override;

	void run() override;

	void update(float, sf::RenderWindow*) override;

	bool isComplete() const override;

private:

	const std::string m_name = "LevelHandlingTest";

	int32_t m_firstLevel;
};

