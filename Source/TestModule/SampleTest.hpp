#pragma once
#include "TestModule/TestBase.hpp"
#include <string>

/* 
* Sample test, which will log something for first 1 second
*/
class SampleTest : public TestBase
{
public:
    const std::string& getName() const override;
    void               setup() override;
    void               run() override;
    void               update(float deltaTime, sf::RenderWindow*) override;
    bool               isComplete() const override;

private:
    const float       MaxRunTime   = 1.0f;
    const std::string Name         = "SampleTest";
    float             m_timePassed = 0.0f;
};