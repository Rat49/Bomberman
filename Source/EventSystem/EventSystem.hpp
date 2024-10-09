#pragma once

#include <functional>
#include <map>
#include <vector>


class EventSystem
{
public:
	static EventSystem& getInstance(); // returns the singleton instance of EventSystem

	using Callback = std::function<void()>; // define a type for the callback function

	int32_t registerEvent(); // function to register a new event and return its unique ID

	void subscribe(int32_t eventID, Callback callback); // subscribe a callback to an event

	void unsubscribe(int32_t eventID, Callback callback); // unsubscribe a callback from an event

	void emit(int32_t eventID); // emit an event to notify all subscribed callbacks

private:
	EventSystem() = default;
	std::map<int32_t, std::vector<Callback>> subscribers; // map to hold event IDs and their associated callbacks
	std::atomic<int32_t> nextEventID{ 0 }; // atomic counter to generate unique event IDs
};
