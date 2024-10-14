#pragma once

#include <functional>
#include <map>
#include <vector>
#include <atomic>

class EventSystem
{
public:
	EventSystem() = default;

	//using Callback = std::function<void()>;

	// Function to register a new event and return its unique ID
	template<typename... Args>
	int32_t registerEvent();

	// Subscribe a callback to an event
	template<typename ReturnType, typename... Args>
	void subscribe(int32_t eventID, std::function<ReturnType(Args...)> callback);

	// UnSubscribe a callback from an event
	template<typename ReturnType, typename... Args>
	void unsubscribe(int32_t eventID, std::function<ReturnType(Args...)> callback);

	// Emit an event to notify all subscribed callbacks
	template<typename... Args>
	void emit(int32_t eventID, Args... args);

private:
	// Map to hold event IDs and their associated callbacks
	std::map<int32_t, std::vector<std::function<void(void*)>>> subscribers;

	// Atomic counter to generate unique event IDs
	std::atomic<int32_t> nextEventID = 0 ;
};



// Template functions should be defined in hpp file

template<typename... Args>
int32_t EventSystem::registerEvent()
{
	return nextEventID++;
}

template<typename ReturnType, typename... Args>
void EventSystem::subscribe(int32_t eventID, std::function<ReturnType(Args...)> callback)
{
	auto wrappedCallback = [callback](void* data) {
		auto args = static_cast<std::tuple<Args...>*>(data);
		std::apply(callback, *args);
		};

	subscribers[eventID].push_back(wrappedCallback);
}

template<typename ReturnType, typename... Args>
void EventSystem::unsubscribe(int32_t eventID, std::function<ReturnType(Args...)> callback)
{
	auto it = subscribers.find(eventID);
	if (it != subscribers.end())
	{
		auto& callbacks = it->second;
		callbacks.erase(std::remove_if(callbacks.begin(), callbacks.end(),
			[&callback](const std::function<void(void*)>& storedCallback) {
				return storedCallback.target_type() == callback.target_type();
			}), callbacks.end());

		if (callbacks.empty())
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
		std::tuple<Args...> data(args...);
		for (const auto& callback : it->second)
		{
			callback(static_cast<void*>(&data));
		}
	}
}