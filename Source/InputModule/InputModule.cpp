#include "InputModule.hpp"
#include "EventSystem/EventSystem.hpp"
#include <iostream>

InputModule::InputModule()
{
	actionID		 = 0;
	InputEventSystem = std::make_unique<EventSystem>();
}

ActionID InputModule::BindAction(const std::string& ActionName, const Button& button)
{
	ActionData newAction        = {};
	newAction.actionName        = ActionName;
	newAction.actionType        = EActionType::ButtonAction;
	newAction.Binding.button    = button;
	newAction.State.buttonState = false;
	newAction.eventID			= InputEventSystem->registerEvent();
	Actions.emplace(actionID, newAction);
	return 	actionID++;
}

ActionID InputModule::BindAxis1D(const std::string& ActionName, const Axis1D& axis1D)
{
	ActionData newAction        = {};
	newAction.actionName        = ActionName;
	newAction.actionType        = EActionType::Axis1DAction;
	newAction.Binding.axis1D    = axis1D;
	newAction.State.axis1DState = 0.0f;
	newAction.eventID			= InputEventSystem->registerEvent();
	Actions.emplace(actionID, newAction);
	return 	actionID++;
}

ActionID InputModule::BindAxis2D(const std::string& ActionName, const Axis2D& axis2D)
{
	ActionData newAction        = {};
	newAction.actionName        = ActionName;
	newAction.actionType        = EActionType::Axis2DAction;
	newAction.Binding.axis2D    = axis2D;
	newAction.State.axis2DState = ZeroVector2D;
	newAction.eventID		    = InputEventSystem->registerEvent();
	Actions.emplace(actionID, newAction);
	return 	actionID++;
}

bool InputModule::GetButtonState(const ActionID ID) const
{
	const auto it = Actions.find(ID);
	if (it != Actions.end() && it->second.actionType == EActionType::ButtonAction)
	{
		return it->second.State.buttonState;
	}
	return false;
}

float InputModule::GetAxis1D(const ActionID ID) const
{
	const auto it = this->Actions.find(ID);
	if (it != Actions.end() && it->second.actionType == EActionType::Axis1DAction)
	{
		return it->second.State.axis1DState;
	}
	return 0.0f;
}

Vector2D InputModule::GetAxis2D(const ActionID ID) const
{
	const auto it = Actions.find(ID);
	if (it != Actions.end() && it->second.actionType == EActionType::Axis2DAction)
	{
		return it->second.State.axis2DState;
	}
	return ZeroVector2D;
}

EventID InputModule::RegisterEvent(const ActionID ID, const Callback& callback)
{
	const auto it = Actions.find(ID);
	if (it != Actions.end())
	{	
		EventID eventID = it->second.eventID;
		InputEventSystem->subscribe(eventID, callback);
		return eventID;
	}
	return -1;
}

bool InputModule::UnregisterEvent(const ActionID ID, const Callback& callback)
{
	const auto it = Actions.find(ID);
	if (it != Actions.end())
	{
		EventID eventID = it->second.eventID;
		InputEventSystem->unsubscribe(eventID, callback);
		return true;
	}
	return false;
}

void InputModule::Update()
{
	for (auto it = Actions.begin(); it != Actions.end(); ++it) {
		EActionType actionType = it->second.actionType;
		switch (actionType)
		{
		case EActionType::ButtonAction:
			if (sf::Keyboard::isKeyPressed(it->second.Binding.button.Key))
			{
				it->second.State.buttonState = true;
				InputEventSystem->emit(it->second.eventID);
			}
			else 
			{
				it->second.State.buttonState = false;
			}
			break;

		case EActionType::Axis1DAction:
			it->second.State.axis1DState = (sf::Keyboard::isKeyPressed(it->second.Binding.axis1D.negativeAxis.Key) ? -1.0f : 0.0f) + (sf::Keyboard::isKeyPressed(it->second.Binding.axis1D.positiveAxis.Key) ? 1.0f : 0.0f);
			if (it->second.State.axis1DState != 0.0f)
			{
				InputEventSystem->emit(it->second.eventID);
			}
			break;

		case EActionType::Axis2DAction:
			it->second.State.axis2DState.x = (sf::Keyboard::isKeyPressed(it->second.Binding.axis2D.Horizontal.negativeAxis.Key) ? -1.0f : 0.0f) + (sf::Keyboard::isKeyPressed(it->second.Binding.axis2D.Horizontal.positiveAxis.Key) ? 1.0f : 0.0f);
			it->second.State.axis2DState.y = (sf::Keyboard::isKeyPressed(it->second.Binding.axis2D.Vertical.negativeAxis.Key) ? 1.0f : 0.0f) + (sf::Keyboard::isKeyPressed(it->second.Binding.axis2D.Vertical.positiveAxis.Key) ? -1.0f : 0.0f);
			if (it->second.State.axis2DState.x != 0.0f || it->second.State.axis2DState.y != 0.0f)
			{
				InputEventSystem->emit(it->second.eventID);
			}
			break;

		default:
			break;
		}
	}
}