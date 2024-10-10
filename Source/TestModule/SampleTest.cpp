#include "TestModule/SampleTest.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"


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

void SampleTest::update(float deltaTime)
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
