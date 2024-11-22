#pragma once
#include "TestModule/TestBase.hpp"
#include "GameModule/PlayerCharacter.hpp"

class BaseLevelTest : public TestBase
{
public:
	const std::string& getName() const override;
	void setup() override;
	void run() override;
	void update(float deltaTime, sf::RenderWindow* window) override;
	bool isComplete() const override;
private:
	const std::string Name = "BaseLevelTest";
	PlayerCharacter player;
	int32_t baseLevel;
};

