#include "InputModuleTest.hpp"
#include "Common/Modules.hpp"
#include "Common/Logs.hpp"
#include <iostream>
#include "InputModule/InputModule.hpp"

const std::string& InputModuleTest::getName() const
{
	return Name;
}

void InputModuleTest::sample_function()
{
	return;
}

void InputModuleTest::setup()
{
	LOG("InputModuleTest: setup()");
	inputModule = new InputModule();
	Button btn = { sf::Keyboard::A };
	int32_t btnID = inputModule->BindAction("Button test", btn);
	inputModule->RegisterEvent(btnID, std::bind(&InputModuleTest::sample_function, this));
}

void InputModuleTest::run()
{
	LOG("InputModuleTest: run()");
	inputModule->Update();
}

bool InputModuleTest::isComplete() const
{
	return true;
}