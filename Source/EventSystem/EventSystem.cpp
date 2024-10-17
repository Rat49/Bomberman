#include "EventSystem/EventSystem.hpp"

int32_t EventSystem::registerEvent()
{
	return nextEventID++;
}

EventSystem::FunctionHandle EventSystem::subscribe(int32_t eventID, Callback callback)
{
	FunctionHandle handle = nextHandleID++;

	subscribers[eventID].push_back({ handle, callback });
	return handle;
}

void EventSystem::unsubscribe(int32_t eventID, FunctionHandle handle)
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

void EventSystem::emit(int32_t eventID, void* param)
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
