#pragma once
#include <SFML/Graphics.hpp>
#include "EventSystem/EventTypes.hpp"
#include <cstdint>

using ActionID = int32_t;

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