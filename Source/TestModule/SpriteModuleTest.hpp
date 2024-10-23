#pragma once

#include <string>
#include "TestModule/TestBase.hpp"
#include "SFML/Graphics.hpp"

class SpriteModule;

class SpriteModuleTest : public TestBase
{
public:
	const std::string& getName() const override;
	void setup() override;
	void run() override;
	void update(float deltaTime) override;
	bool isComplete() const override;

private:

	const std::string name = "SpriteModuleTest";
	int32_t m_animationId;
	sf::RenderWindow m_window;
};

