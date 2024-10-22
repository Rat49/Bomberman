#pragma once

#include <map>
#include <functional>
#include <vector>
#include <string>
#include <atomic>
#include <utility>
#include <SFML/Graphics.hpp>
#include "EventSystem/EventSystem.hpp"
#include "Common/FloatUtils.hpp"
#include "Common/Logs.hpp"
#include "Common/Modules.hpp"

using ActionID       = int32_t;
using EventID        = int32_t;

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

struct ActionData {
	std::string actionName;
	EActionType actionType;
	EventID eventID;

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

	ActionID BindAction(const std::string& actionName, const Button& button);

	ActionID BindAxis1D(const std::string& actionName, const Axis1D& axis1D);

	ActionID BindAxis2D(const std::string& actionName, const Axis2D& axis2);

	FunctionHandle RegisterEvent(ActionID ID, Callback callback);

	bool UnregisterEvent(ActionID ID, FunctionHandle functionHandle);

	bool GetButtonState(ActionID ID) const;

	float GetAxis1D(ActionID ID) const;

	sf::Vector2f GetAxis2D(ActionID ID) const;

	void Update();

private:
	std::atomic<ActionID> actionID;

	std::map<ActionID, ActionData> actions;

	std::map<ActionID, std::vector<FunctionHandle>> events;
};

