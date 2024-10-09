#include "EventSystem.hpp"

EventSystem& EventSystem::getInstance()
{
	static EventSystem instance;
	return instance;
}

int32_t EventSystem::registerEvent()
{
	// Return the current ID and increment it for the next event
	return nextEventID++;
}

void EventSystem::subscribe(int32_t eventID, Callback callback)
{
	auto& callbacks = subscribers[eventID];

	// Check if the callback is already subscribed
	auto it = std::find_if(callbacks.begin(), callbacks.end(),
		[&callback](const Callback& c) {
			return c.target_type() == callback.target_type();
		});

	// Add the callback if it is not already subscribed
	if (it == callbacks.end())
	{
		callbacks.push_back(callback);
	}
}

void EventSystem::unsubscribe(int32_t eventID, Callback callback)
{
	auto it = subscribers.find(eventID);

	// If the event exists, remove the specified callback
	if (it != subscribers.end())
	{
		auto& callbacks = it->second;
		callbacks.erase(std::remove_if(callbacks.begin(), callbacks.end(),
			[&callback](const Callback& c) {
				return c.target_type() == callback.target_type();
			}), callbacks.end());

		// Remove the event if no more callbacks exist
		if (callbacks.empty())
		{
			subscribers.erase(it);
		}
	}
}

void EventSystem::emit(int32_t eventID)
{
	auto it = subscribers.find(eventID);

	// Trigger all callbacks for the event if it exists
	if (it != subscribers.end())
	{
		for (const auto& callback : it->second)
		{
			callback();
		}
	}
}
