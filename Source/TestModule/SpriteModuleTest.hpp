#pragma once

#include "TestModule/TestBase.hpp"
#include <string>

class SpriteModuleTest : public TestBase
{
public:
    const std::string& getName() const override;
    void               setup() override;
    void               run() override;
    void               update(float deltaTime, sf::RenderWindow*) override;
    bool               isComplete() const override;

private:
    const std::string name = "SpriteModuleTest";
    int32_t           m_animationId;
};
