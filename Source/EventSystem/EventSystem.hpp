#pragma once

#include <functional>
#include <map>
#include <vector>
#include <atomic>
#include "EventTypes.hpp"
#include "BaseModule/BaseModule.hpp"

class EventSystem : public BaseModule
{
public:
	EventSystem() = default;

	// Function to register a new event and return its unique ID
	EventID registerEvent();

	// Subscribe a callback to an event
	FunctionHandle subscribe(EventID eventID, Callback callback);

	// UnSubscribe a callback from an event
	void unsubscribe(EventID eventID, FunctionHandle handle);

	// Emit an event to notify all subscribed callbacks
	void emit(EventID eventID, void* param);

	void terminate() override;

private:
	struct Subscriber 
	{
		FunctionHandle handle;
		Callback callback;
	};

	// Map to hold event IDs and their associated callbacks
	std::map<EventID, std::vector<Subscriber>> subscribers;

	// Atomic counter to generate unique event IDs
	std::atomic<EventID> nextEventID = 0;
	std::atomic<FunctionHandle> nextHandleID = 0;
};