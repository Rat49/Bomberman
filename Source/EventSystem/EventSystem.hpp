#pragma once

#include <functional>
#include <map>
#include <vector>
#include <atomic>

class EventSystem
{
public:
	EventSystem() = default;

	using Callback = std::function<void()>;

	// Function to register a new event and return its unique ID
	int32_t registerEvent();

	// Subscribe a callback to an event
	void subscribe(int32_t eventID, Callback callback);

	// UnSubscribe a callback from an event
	void unsubscribe(int32_t eventID, Callback callback);

	// Emit an event to notify all subscribed callbacks
	void emit(int32_t eventID);

private:
	// Map to hold event IDs and their associated callbacks
	std::map<int32_t, std::vector<Callback>> subscribers;

	// Atomic counter to generate unique event IDs
	std::atomic<int32_t> nextEventID = 0 ;
};