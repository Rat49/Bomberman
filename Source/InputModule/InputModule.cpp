#include "InputModule.hpp"
#include "EventSystem/EventSystem.hpp"
#include <iostream>

InputModule::InputModule()
{
	actionID = 0;
}

InputModule::~InputModule()
{
	for (auto it = actions.begin(); it != actions.end(); ++it)
	{
		if (it->second.eventID == -1)
		{
			LOG("Action %s, event wasn't unregisterd, EventID: %d ", it->second.actionName, it->second.eventID);
		}
		
		for (int i = 0; i < events[it->second.actionID].size(); ++i)
		{
			Modules::Events->unsubscribe(it->second.eventID, events[it->second.actionID][i]);
		}

		events[it->second.actionID].clear();
		events.erase(it->second.actionID);
	}
}

ActionID InputModule::BindAction(const std::string& actionName, const Button& button, TriggerState triggerState)
{
	ActionData newAction        = {};
	newAction.actionName        = actionName;
	newAction.actionType        = EActionType::ButtonAction;
	newAction.actionID          = actionID;
	newAction.Binding.button    = button;
	newAction.State.buttonState = false;
	newAction.eventID           = -1;
	newAction.triggerState      = triggerState;
	actions.emplace(actionID, std::move(newAction));
	return 	actionID++;
}

ActionID InputModule::BindAxis1D(const std::string& actionName, const Axis1D& axis1D, TriggerState triggerState)
{
	ActionData newAction        = {};
	newAction.actionName        = actionName;
	newAction.actionType        = EActionType::Axis1DAction;
	newAction.actionID          = actionID;
	newAction.Binding.axis1D    = axis1D;
	newAction.State.axis1DState = 0.0f;
	newAction.eventID			= -1;
	newAction.triggerState      = triggerState;
	actions.emplace(actionID, std::move(newAction));
	return 	actionID++;
}

ActionID InputModule::BindAxis2D(const std::string& actionName, const Axis2D& axis2D, TriggerState triggerState)
{
	ActionData newAction        = {};
	newAction.actionName        = actionName;
	newAction.actionType        = EActionType::Axis2DAction;
	newAction.actionID          = actionID;
	newAction.Binding.axis2D    = axis2D;
	newAction.State.axis2DState = sf::Vector2f(0.0f, 0.0f);
	newAction.eventID		    = -1;
	newAction.triggerState      = triggerState;
	actions.emplace(actionID, std::move(newAction));
	return 	actionID++;
}

bool InputModule::GetButtonState(ActionID ID) const
{
	const auto it = actions.find(ID);
	if (it != actions.end() && it->second.actionType == EActionType::ButtonAction)
	{
		return it->second.State.buttonState;
	}
	return false;
}

float InputModule::GetAxis1D(ActionID ID) const
{
	const auto it = this->actions.find(ID);
	if (it != actions.end() && it->second.actionType == EActionType::Axis1DAction)
	{
		return it->second.State.axis1DState;
	}
	return 0.0f;
}

Vector2D InputModule::GetAxis2D(ActionID ID) const
{
	const auto it = actions.find(ID);
	if (it != actions.end() && it->second.actionType == EActionType::Axis2DAction)
	{
		return it->second.State.axis2DState;
	}
	return sf::Vector2f(0.0f, 0.0f);
}

FunctionHandle InputModule::RegisterEvent(ActionID ID, Callback callback)
{
	const auto it = actions.find(ID);
	if (it == actions.end())
	{
		return -1;
	}

	if (it->second.eventID == -1)
	{
		it->second.eventID = Modules::Events->registerEvent();
	}

	EventID eventID               = it->second.eventID;
	FunctionHandle functionHandle = Modules::Events->subscribe(eventID, callback);
	events[ID].push_back(functionHandle);
	return functionHandle;
}

bool InputModule::UnregisterEvent(ActionID ID, FunctionHandle functionHandle)
{
	const auto it = actions.find(ID);
	if (it == actions.end())
	{
		return false;
	}

	if (it->second.eventID == -1)
	{
		return false;
	}

	EventID eventID = it->second.eventID;
	Modules::Events->unsubscribe(eventID, functionHandle);
	for (int i = 0; i < events[ID].size(); ++i)
	{
		if (events[ID][i] == functionHandle)
		{
			events[ID].erase(events[ID].begin() + i);
		}
	}

	if (events[ID].empty())
	{
		events.erase(ID);
		it->second.eventID = -1;
	}
	return true;
}

bool InputModule::isAlmostZero(float x) {
	return std::fabs(x) < std::numeric_limits<float>::epsilon();
}

void InputModule::Update()
{
	for (auto it = actions.begin(); it != actions.end(); ++it) {
		EActionType actionType    = it->second.actionType;
		TriggerState triggerState = it->second.triggerState;
		EventID eventID           = it->second.eventID;

		switch (actionType)
		{
		case EActionType::ButtonAction:
			it->second.State.buttonState = sf::Keyboard::isKeyPressed(it->second.Binding.button.Key);
			if (eventID == -1)
			{
				break;
			}

			if (triggerState == TriggerState::Active && it->second.State.buttonState)
			{	
				auto params = new ButtonState{ it->second.State.buttonState };
				Modules::Events->emit(it->second.eventID, params);
			}
			else if (triggerState == TriggerState::Inactive && !it->second.State.buttonState)
			{
				auto params = new ButtonState{ it->second.State.buttonState };
				 Modules::Events->emit(it->second.eventID, params);
			}
			break;

		case EActionType::Axis1DAction:
			it->second.State.axis1DState = (sf::Keyboard::isKeyPressed(it->second.Binding.axis1D.negativeAxis.Key) ? -1.0f : 0.0f) + (sf::Keyboard::isKeyPressed(it->second.Binding.axis1D.positiveAxis.Key) ? 1.0f : 0.0f);
			if (eventID == -1)
			{
				break;
			}

			if (triggerState == TriggerState::Active && !isAlmostZero(it->second.State.axis1DState))
			{
				auto params = new Axis1DState{ it->second.State.axis1DState };
				Modules::Events->emit(it->second.eventID, params);
			}
			else if (triggerState == TriggerState::Inactive && isAlmostZero(it->second.State.axis1DState))
			{
				auto params = new Axis1DState{ it->second.State.axis1DState };
				Modules::Events->emit(it->second.eventID, params);
			}
			break;

		case EActionType::Axis2DAction:
			it->second.State.axis2DState.x = (sf::Keyboard::isKeyPressed(it->second.Binding.axis2D.Horizontal.negativeAxis.Key) ? -1.0f : 0.0f) + (sf::Keyboard::isKeyPressed(it->second.Binding.axis2D.Horizontal.positiveAxis.Key) ? 1.0f : 0.0f);
			it->second.State.axis2DState.y = (sf::Keyboard::isKeyPressed(it->second.Binding.axis2D.Vertical.negativeAxis.Key) ? 1.0f : 0.0f) + (sf::Keyboard::isKeyPressed(it->second.Binding.axis2D.Vertical.positiveAxis.Key) ? -1.0f : 0.0f);
			if (eventID == -1)
			{
				break;
			}

			if (triggerState == TriggerState::Active && (!isAlmostZero(it->second.State.axis2DState.x) || !isAlmostZero(it->second.State.axis2DState.y)))
			{
				auto params = new Axis2DState{ sf::Vector2f(it->second.State.axis2DState.x, it->second.State.axis2DState.y) };
				Modules::Events->emit(it->second.eventID, params);
			}
			else if (triggerState == TriggerState::Inactive && (isAlmostZero(it->second.State.axis2DState.x) && isAlmostZero(it->second.State.axis2DState.y)))
			{
				auto params = new Axis2DState{ sf::Vector2f(it->second.State.axis2DState.x, it->second.State.axis2DState.y) };
				Modules::Events->emit(it->second.eventID, params);
			}
			break;

		default:
			break;

		}
	}
}