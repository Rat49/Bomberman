#pragma once
#include "InputModule/InputModule.hpp"
#include "TestModule/TestBase.hpp"
#include <SFML/Graphics.hpp>

class AssetManagerTest : public TestBase
{
public:
    const std::string& getName() const override;
    void               setup() override;
    void               run() override;
    void               update(float deltaTime, sf::RenderWindow* window) override;
    bool               isComplete() const override;

private:
    const std::string Name = "AssetManagerTest";
};
