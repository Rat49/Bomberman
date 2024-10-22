#include "InputModule.hpp"
#include "EventSystem/EventSystem.hpp"

InputModule::InputModule()
{
	actionID = 0;
}

InputModule::~InputModule()
{
	for (auto it = actions.begin(); it != actions.end(); ++it)
	{
		if (it->second.eventID != -1)
		{
			LOG("Action $ with ID: $, event wasn't unregisterd, EventID: $ ", it->second.actionName, it->first, it->second.eventID);
		}
		
		for (int i = 0; i < events[it->first].size(); ++i)
		{
			Modules::Events->unsubscribe(it->second.eventID, events[it->first][i]);
		}
	}
}

ActionID InputModule::BindAction(const std::string& actionName, const Button& button)
{
	ActionData newAction        = {};
	newAction.actionName        = actionName;
	newAction.actionType        = EActionType::ButtonAction;
	newAction.Binding.button    = button;
	newAction.State.buttonState = false;
	newAction.eventID           = -1;
	actions.emplace(actionID, std::move(newAction));
	return 	actionID++;
}

ActionID InputModule::BindAxis1D(const std::string& actionName, const Axis1D& axis1D)
{
	ActionData newAction        = {};
	newAction.actionName        = actionName;
	newAction.actionType        = EActionType::Axis1DAction;
	newAction.Binding.axis1D    = axis1D;
	newAction.State.axis1DState = 0.0f;
	newAction.eventID			= -1;
	actions.emplace(actionID, std::move(newAction));
	return 	actionID++;
}

ActionID InputModule::BindAxis2D(const std::string& actionName, const Axis2D& axis2D)
{
	ActionData newAction        = {};
	newAction.actionName        = actionName;
	newAction.actionType        = EActionType::Axis2DAction;
	newAction.Binding.axis2D    = axis2D;
	newAction.State.axis2DState = sf::Vector2f(0.0f, 0.0f);
	newAction.eventID		    = -1;
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

sf::Vector2f InputModule::GetAxis2D(ActionID ID) const
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

	for (auto event_it = events[ID].begin(); event_it != events[ID].end(); ++event_it)
	{
		if (*event_it == functionHandle)
		{
			events[ID].erase(event_it);
			break;
		}
	}

	if (events[ID].empty())
	{
		events.erase(ID);
		it->second.eventID = -1;
	}
	return true;
}

void InputModule::Update()
{
	for (auto& action : actions)
	{
		EActionType actionType = action.second.actionType;
		EventID eventID        = action.second.eventID;
		bool shouldEmit        = (action.second.eventID != -1) ? true : false;
		void* params           = nullptr;
		switch (actionType)
		{
		case EActionType::ButtonAction:
			action.second.State.buttonState = sf::Keyboard::isKeyPressed(action.second.Binding.button.Key);
			shouldEmit                   = shouldEmit && action.second.State.buttonState;
			params                       = &action.second.State.buttonState;
			break;

		case EActionType::Axis1DAction:
			action.second.State.axis1DState = (sf::Keyboard::isKeyPressed(action.second.Binding.axis1D.negativeAxis.Key) ? -1.0f : 0.0f) + (sf::Keyboard::isKeyPressed(action.second.Binding.axis1D.positiveAxis.Key) ? 1.0f : 0.0f);
			shouldEmit                      = shouldEmit && (!FloatUtils::isAlmostZero(action.second.State.axis1DState));
			params                          = &action.second.State.axis1DState;
			break;

		case EActionType::Axis2DAction:
			action.second.State.axis2DState.x = (sf::Keyboard::isKeyPressed(action.second.Binding.axis2D.Horizontal.negativeAxis.Key) ? -1.0f : 0.0f) + (sf::Keyboard::isKeyPressed(action.second.Binding.axis2D.Horizontal.positiveAxis.Key) ? 1.0f : 0.0f);
			action.second.State.axis2DState.y = (sf::Keyboard::isKeyPressed(action.second.Binding.axis2D.Vertical.negativeAxis.Key) ? 1.0f : 0.0f) + (sf::Keyboard::isKeyPressed(action.second.Binding.axis2D.Vertical.positiveAxis.Key) ? -1.0f : 0.0f);
			shouldEmit                        = shouldEmit && (!FloatUtils::isAlmostZero(action.second.State.axis2DState.x) || !FloatUtils::isAlmostZero(action.second.State.axis2DState.y));
			params                            = &action.second.State.axis2DState;
			break;

		default:
			break;
	}
		if (shouldEmit) Modules::Events->emit(eventID, params);
	}
}