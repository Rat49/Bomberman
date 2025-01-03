#pragma once
#include "GameModule/PlayerCharacter.hpp"
#include "TestModule/TestBase.hpp"
#include <iostream>

class PlayerTest : public TestBase
{
public:
    const std::string& getName() const override;
    void               setup() override;
    void               run() override;
    void               update(float deltaTime, sf::RenderWindow*) override;
    bool               isComplete() const override;

private:
    const std::string Name = "PlayerTest";
    PlayerCharacter   player;
};
