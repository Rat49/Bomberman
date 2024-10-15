#pragma once

#include <functional>
#include <map>
#include <vector>
#include <atomic>
#include <typeindex>

class EventSystem
{
public:
	EventSystem() = default;

	using FunctionHandle = int32_t;

	// Function to register a new event and return its unique ID
	template<typename... Args>
	int32_t registerEvent();

	// Subscribe a callback to an event
	template<typename ReturnType, typename... Args>
	FunctionHandle  subscribe(int32_t eventID, std::function<ReturnType(Args...)> callback);

	// UnSubscribe a callback from an event
	template<typename ReturnType, typename... Args>
	void unsubscribe(int32_t eventID, FunctionHandle handle);

	// Emit an event to notify all subscribed callbacks
	template<typename... Args>
	void emit(int32_t eventID, Args... args);

private:
	struct Subscriber {
		FunctionHandle handle;
		std::function<void(void*)> callback;
		std::type_index callbackType;
	};

	// Map to hold event IDs and their associated callbacks
	std::map<int32_t, std::vector<Subscriber>> subscribers;

	// Atomic counter to generate unique event IDs
	std::atomic<int32_t> nextEventID = 0 ;
	std::atomic<int32_t> nextHandleID = 0;
};



// Template functions should be defined in hpp file

template<typename... Args>
int32_t EventSystem::registerEvent()
{
	return nextEventID++;
}

template<typename ReturnType, typename... Args>
EventSystem::FunctionHandle EventSystem::subscribe(int32_t eventID, std::function<ReturnType(Args...)> callback)
{
	FunctionHandle handle = nextHandleID++;

	auto wrappedCallback = [callback](void* data) {
		auto args = static_cast<std::tuple<Args...>*>(data);
		std::apply(callback, *args);
		};

	subscribers[eventID].push_back({ handle, wrappedCallback, typeid(callback) });
	return handle;
}

template<typename ReturnType, typename... Args>
void EventSystem::unsubscribe(int32_t eventID, FunctionHandle handle)
{
	auto it = subscribers.find(eventID);

	if (it != subscribers.end())
	{
		auto& callbackList = it->second;

		// Remove a callback based on its handle
		callbackList.erase(
			std::remove_if(callbackList.begin(), callbackList.end(),
				[handle](const Subscriber& sub) {
					return sub.handle == handle;
				}),
			callbackList.end());

		// If there are no more callbacks, remove the event
		if (callbackList.empty())
		{
			subscribers.erase(it);
		}
	}
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