#include "TestModule/SampleTest.hpp"
#include "Common/Logs.hpp"
#include "Common/Modules.hpp"


const std::string& SampleTest::getName() const
{
    return Name;
}

void SampleTest::setup()
{
    LOG("SampleTest: setup()");
    m_timePassed = 0;
}

void SampleTest::run()
{
    LOG("SampleTest: run()");
}

void SampleTest::update(float deltaTime, sf::RenderWindow*)
{
    if (!isComplete())
    {
        m_timePassed += deltaTime;
        LOG("SampleTest: update(). $ seconds passed", m_timePassed);
    }
}

bool SampleTest::isComplete() const
{
    return m_timePassed > MaxRunTime;
}
