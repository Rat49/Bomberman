#include "EventSystem/EventSystem.hpp"

EventID EventSystem::registerEvent()
{
	return nextEventID++;
}

FunctionHandle EventSystem::subscribe(EventID eventID, Callback callback)
{
	FunctionHandle handle = nextHandleID++;

	subscribers[eventID].push_back({ handle, std::move(callback) });
	return handle;
}

void EventSystem::unsubscribe(EventID eventID, FunctionHandle handle)
{
	auto it = subscribers.find(eventID);

	if (it != subscribers.end())
	{
		auto& callbackList = it->second;

		// Remove a callback based on its handle
		callbackList.erase(
			std::remove_if(callbackList.begin(), callbackList.end(),
				[handle](const Subscriber& sub)
				{
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

void EventSystem::emit(EventID eventID, void* param)
{
	auto it = subscribers.find(eventID);
	if (it != subscribers.end())
	{
		for (const auto& subscriber : it->second)
		{
			// Call each declared callback with the parameter passed
			subscriber.callback(param);
		}
	}
}
