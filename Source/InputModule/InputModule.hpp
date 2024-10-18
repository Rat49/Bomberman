#pragma once

#include <map>
#include <functional>
#include <vector>
#include <string>
#include <atomic>
#include <utility>
#include <SFML/Graphics.hpp>
#include "Common/Logs.hpp"
#include "Common/Modules.hpp"

using ActionID       = int32_t;
using EventID        = int32_t;
using Vector2D       = sf::Vector2f;
using FunctionHandle = int32_t;
using Callback       = std::function<void(void*)>;

enum TriggerState 
{
	Active,
	Inactive
};

struct Button
{
	sf::Keyboard::Key Key = sf::Keyboard::Unknown;
};

struct Axis1D
{
	Button negativeAxis;
	Button positiveAxis;
};

struct Axis2D
{
	Axis1D Vertical;
	Axis1D Horizontal;
};

enum class EActionType
{
	ButtonAction,
	Axis1DAction,
	Axis2DAction
};

struct ButtonState
{
	bool buttonState;
};

struct Axis1DState
{
	float axis1DState;
};

struct Axis2DState
{
	sf::Vector2f axis2DState;
};

struct ActionData {
	std::string actionName;
	EActionType actionType;
	ActionID actionID;
	EventID eventID;
	TriggerState triggerState;

	union BindingUnion {
		Button button;
		Axis1D axis1D;
		Axis2D axis2D;
	}Binding;

	union StateUnion {
		sf::Vector2f axis2DState;
		float axis1DState;
		bool buttonState;
	}State;
};

class InputModule
{
public:
	InputModule();

	~InputModule();

	ActionID BindAction(const std::string& actionName, const Button& button, TriggerState triggerState);

	ActionID BindAxis1D(const std::string& actionName, const Axis1D& axis1D, TriggerState triggerState);

	ActionID BindAxis2D(const std::string& actionName, const Axis2D& axis2, TriggerState triggerState);

	FunctionHandle RegisterEvent(ActionID ID, Callback callback);

	bool UnregisterEvent(ActionID ID, FunctionHandle functionHandle);

	bool GetButtonState(ActionID ID) const;

	float GetAxis1D(ActionID ID) const;

	sf::Vector2f GetAxis2D(ActionID ID) const;

	void Update();

private:
	bool isAlmostZero(float x);

	std::atomic<ActionID> actionID;

	std::map<ActionID, ActionData> actions;

	std::map<ActionID, std::vector<int32_t>> events;
};

