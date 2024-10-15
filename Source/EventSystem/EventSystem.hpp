#pragma once

#include <functional>
#include <map>
#include <vector>
#include <atomic>

class EventSystem
{
public:
	EventSystem() = default;

	using FunctionHandle = int32_t;

	// Function to register a new event and return its unique ID
	int32_t registerEvent();

	// Subscribe a callback to an event
	template<typename... Args>
	FunctionHandle subscribe(int32_t eventID, std::function<void(Args...)> callback);

	// UnSubscribe a callback from an event
	void unsubscribe(int32_t eventID, FunctionHandle handle);

	// Emit an event to notify all subscribed callbacks
	template<typename... Args>
	void emit(int32_t eventID, Args... args);

private:
	struct Subscriber {
		FunctionHandle handle;
		std::function<void(void*)> callback;
	};

	// Map to hold event IDs and their associated callbacks
	std::map<int32_t, std::vector<Subscriber>> subscribers;

	// Atomic counter to generate unique event IDs
	std::atomic<int32_t> nextEventID = 0 ;
	std::atomic<int32_t> nextHandleID = 0;
};



// Template functions should be defined in hpp file

template<typename... Args>
EventSystem::FunctionHandle EventSystem::subscribe(int32_t eventID, std::function<void(Args...)> callback)
{
	FunctionHandle handle = nextHandleID++;

	auto wrappedCallback = [callback](void* data) {
		auto args = static_cast<std::tuple<Args...>*>(data);
		std::apply(callback, *args);
		};

	subscribers[eventID].push_back({ handle, wrappedCallback });
	return handle;
}

template<typename... Args>
void EventSystem::emit(int32_t eventID, Args... args)
{
	auto it = subscribers.find(eventID);
	if (it != subscribers.end())
	{
		auto argsTuple = std::make_tuple(args...);

		for (const auto& subscriber : it->second)
		{
			// Call each declared callback with the arguments passed
			subscriber.callback(&argsTuple);
		}
	}
}