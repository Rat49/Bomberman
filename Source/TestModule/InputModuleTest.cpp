#include "InputModuleTest.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"

const std::string& InputModuleTest::getName() const
{
	return Name;
}

void InputModuleTest::buttonTest(void* buttonState)
{
	bool state = *reinterpret_cast<bool*>(buttonState);
	LOG("InputModuleTest button binding test: $", state);
}

void InputModuleTest::axis1DTest(void* axis1DState)
{
	float state = *reinterpret_cast<float*>(axis1DState);
	LOG("InputModuleTest button binding test: $", state);
}

void InputModuleTest::axis2DTest(void* axis2DState)
{
	sf::Vector2f state = *reinterpret_cast<sf::Vector2f*>(axis2DState);
	LOG("InputModuleTest button binding test: $:$", state.x, state.y);
}

void InputModuleTest::setup()
{
	LOG("InputModuleTest: setup()");

	Button buttonA              = { sf::Keyboard::A };
	ActionID buttonActionID     = Modules::Input->BindAction("Button test", buttonA);
	FunctionHandle buttonHandle = Modules::Input->RegisterEvent(buttonActionID, std::bind(&InputModuleTest::buttonTest, this, std::placeholders::_1));

	bindedFunctions++;

	Axis1D axis1D;
	axis1D.negativeAxis.Key     = sf::Keyboard::Q;
	axis1D.positiveAxis.Key     = sf::Keyboard::W;
	ActionID axis1DActionID     = Modules::Input->BindAxis1D("Axis1D test", axis1D);
	FunctionHandle axis1DHandle = Modules::Input->RegisterEvent(axis1DActionID, std::bind(&InputModuleTest::axis1DTest, this, std::placeholders::_1));

	bindedFunctions++;

	Button up                   = { sf::Keyboard::Up };
	Button down                 = { sf::Keyboard::Down };
	Button left                 = { sf::Keyboard::Left };
	Button right                = { sf::Keyboard::Right };
	Axis2D axis2D;
	axis2D.Horizontal           = { left, right };
	axis2D.Vertical             = { down, up };
	ActionID axis2DActionID     = Modules::Input->BindAxis2D("Axis2D test", axis2D);
	FunctionHandle axis2DHandle = Modules::Input->RegisterEvent(axis2DActionID, std::bind(&InputModuleTest::axis2DTest, this, std::placeholders::_1));

	bindedFunctions++;

	Modules::Input->UnregisterEvent(buttonActionID, buttonHandle);
	Modules::Input->UnregisterEvent(axis1DActionID, axis1DHandle);
	Modules::Input->UnregisterEvent(axis2DActionID, axis2DHandle);
}

void InputModuleTest::run()
{
	LOG("InputModuleTest: run()");
}

void InputModuleTest::update(float, sf::RenderWindow*)
{
	LOG("InputModuleTest: update()");
}

bool InputModuleTest::isComplete() const
{
	return bindedFunctions == numberOfFunctions;
}