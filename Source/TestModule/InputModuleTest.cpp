#include "InputModuleTest.hpp"
#include "Common/Logs.hpp"
#include "Common/Modules.hpp"

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

    Modules::Input->LoadInputSettings("../../Data/Config/test_input_config.ini");


    ActionID buttonActionID = Modules::Input->GetActionID("PlantBomb");
    FunctionHandle
        buttonHandle = Modules::Input->RegisterEvent(buttonActionID,
                                                     std::bind(&InputModuleTest::buttonTest, this, std::placeholders::_1));

    bindedFunctions++;

    ActionID axis1DActionID = Modules::Input->GetActionID("MoveLeftRight");
    FunctionHandle
        axis1DHandle = Modules::Input->RegisterEvent(axis1DActionID,
                                                     std::bind(&InputModuleTest::axis1DTest, this, std::placeholders::_1));

    bindedFunctions++;

    ActionID axis2DActionID = Modules::Input->GetActionID("PlayerMovement");
    FunctionHandle
        axis2DHandle = Modules::Input->RegisterEvent(axis2DActionID,
                                                     std::bind(&InputModuleTest::axis2DTest, this, std::placeholders::_1));

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