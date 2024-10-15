#pragma once

#include <unordered_map>
#include <functional>
#include <vector>
#include <string>
#include <atomic>
#include <SFML/Graphics.hpp>

class EventSystem;

using ActionID = int32_t;
using EventID  = int32_t;
using Vector2D = sf::Vector2f;
using Callback = std::function<void()>;
const Vector2D ZeroVector2D(0.0f, 0.0f);

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
		Vector2D axis2DState;
		float axis1DState;
		bool buttonState;
	}State;
};

class InputModule
{
public:
	InputModule();

	ActionID BindAction(const std::string& ActionName, const Button& button);

	ActionID BindAxis1D(const std::string& ActionName, const Axis1D& axis1D);

	ActionID BindAxis2D(const std::string& ActionName, const Axis2D& axis2);

	EventID RegisterEvent(const ActionID ID, const Callback& callback);

	bool UnregisterEvent(const ActionID ID, const Callback& callback);

	bool GetButtonState(const ActionID ID) const;

	float GetAxis1D(const ActionID ID) const;

	Vector2D GetAxis2D(const ActionID ID) const;

	void Update();

private:
	std::atomic<ActionID> actionID;

	std::unique_ptr<EventSystem> InputEventSystem;

	std::unordered_map<ActionID, ActionData> Actions;
};