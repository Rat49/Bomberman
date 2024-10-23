#pragma once

#include <map>
#include <vector>
#include <string>
#include <atomic>
#include <SFML/Graphics.hpp>
#include "InputTypes.hpp"

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

