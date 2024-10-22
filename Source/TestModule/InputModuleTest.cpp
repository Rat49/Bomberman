#include "InputModuleTest.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"

const std::string& InputModuleTest::getName() const
{
	return Name;
}

void InputModuleTest::buttonTest(bool state)
{
	LOG("InputModuleTest button binding test: $", state);
}

void InputModuleTest::axis1DTest(float state)
{
	LOG("InputModuleTest button binding test: $", state);
}

void InputModuleTest::axis2DTest(sf::Vector2f state)
{
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
	FunctionHandle axis1DHandle = Modules::Input->RegisterEvent(axis1DActionID, std::bind(
		[](void* data, InputModuleTest* instance) {
			float* floatValue = static_cast<float*>(data);
			instance->axis1DTest(*floatValue);
		},
		std::placeholders::_1,
		this
	));

	bindedFunctions++;

	Button up                   = { sf::Keyboard::Up };
	Button down                 = { sf::Keyboard::Down };
	Button left                 = { sf::Keyboard::Left };
	Button right                = { sf::Keyboard::Right };
	Axis2D axis2D;
	axis2D.Horizontal           = { left, right };
	axis2D.Vertical             = { down, up };
	ActionID axis2DActionID     = Modules::Input->BindAxis2D("Axis2D test", axis2D);
	FunctionHandle axis2DHandle = Modules::Input->RegisterEvent(axis2DActionID, std::bind(
		[](void* data, InputModuleTest* instance) {
			sf::Vector2f* vecData = static_cast<sf::Vector2f*>(data);
			instance->axis2DTest(*vecData);
		},
		std::placeholders::_1,
		this
	));

	bindedFunctions++;

	Modules::Input->UnregisterEvent(buttonActionID, buttonHandle);
	Modules::Input->UnregisterEvent(axis1DActionID, axis1DHandle);
	Modules::Input->UnregisterEvent(axis2DActionID, axis2DHandle);
}

void InputModuleTest::run()
{
	LOG("InputModuleTest: run()");
}

void InputModuleTest::update(float)
{
	LOG("InputModuleTest: update()");
	Modules::Input->Update();
}

bool InputModuleTest::isComplete() const
{
	return bindedFunctions == numberOfFunctions;
}