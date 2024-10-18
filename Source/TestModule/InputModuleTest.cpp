#include "InputModuleTest.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"
#include <iostream>

const std::string& InputModuleTest::getName() const
{
	return Name;
}

void InputModuleTest::buttonTest(bool)
{
	LOG("InputModuleTest button binding test");
	passedTestsCount = passedTestsCount + 1;
}

void InputModuleTest::axis1DTest(float)
{
	LOG("InputModuleTest axis1D binding test");
	passedTestsCount += 1;
}

void InputModuleTest::axis2DTest(sf::Vector2f)
{
	LOG("InputModuleTest axis2D binding test");
	passedTestsCount += 1;
}

void InputModuleTest::setup()
{
	LOG("InputModuleTest: setup()");
	inputModule = std::make_unique<InputModule>();

	Button buttonA         = { sf::Keyboard::A };
	int32_t buttonActionID = inputModule->BindAction("Button test", buttonA, TriggerState::Inactive);
	inputModule->RegisterEvent(buttonActionID, std::bind(&InputModuleTest::buttonTest, this, std::placeholders::_1));

	Axis1D axis1D;
	axis1D.negativeAxis.Key = sf::Keyboard::Q;
	axis1D.positiveAxis.Key = sf::Keyboard::W;
	int32_t axis1DActionID  = inputModule->BindAxis1D("Axis1D test", axis1D, TriggerState::Inactive);
	inputModule->RegisterEvent(axis1DActionID, [this](void* data)
		{
			auto params = static_cast<Axis1DState*>(data);
			this->axis1DTest(params->axis1DState); 
		}
	);

	Button up              = { sf::Keyboard::Up };
	Button down            = { sf::Keyboard::Down };
	Button left            = { sf::Keyboard::Left };
	Button right           = { sf::Keyboard::Right };
	Axis2D axis2D;
	axis2D.Horizontal      = { left, right };
	axis2D.Vertical        = { down, up };
	int32_t axis2DActionID = inputModule->BindAxis2D("Axis2D test", axis2D, TriggerState::Inactive);
	inputModule->RegisterEvent(axis2DActionID, [this](void* data)
		{
			auto params = static_cast<Axis2DState*>(data);
			this->axis2DTest(params->axis2DState);
		});
}

void InputModuleTest::run()
{
	LOG("InputModuleTest: run()");
}

void InputModuleTest::update(float)
{
	LOG("InputModuleTest: update()");
	inputModule->Update();
}

bool InputModuleTest::isComplete() const
{
	return passedTestsCount >= numberOfTests;
}