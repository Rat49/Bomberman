#pragma once

#include "TestModule/TestBase.hpp"
#include <SFML/Graphics.hpp>

class SoundSystemTest : public TestBase
{
public:
    const std::string& getName() const override;

    void setup() override;

    void run() override;

    void update(float, sf::RenderWindow*) override;

    bool isComplete() const override;

private:
    const std::string m_name = "SoundSystemTest";
};
