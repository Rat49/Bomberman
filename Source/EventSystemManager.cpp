#include "EventSystemManager.hpp"

EventSystemManager& EventSystemManager::GetInstance() 
{
	static EventSystemManager Instance;
	return Instance;
}

void EventSystemManager::Subscribe(EventID event, Callback callback) 
{
	auto& callbacks = Subscribers[event];
	auto it = std::find_if(callbacks.begin(), callbacks.end(),
		[&callback](const Callback& c) {
			return c.target_type() == callback.target_type();
		});

	if (it == callbacks.end()) 
	{
		callbacks.push_back(callback);
	}
}

void EventSystemManager::Unsubscribe(EventID event, Callback callback) 
{
	auto it = Subscribers.find(event);
	if (it != Subscribers.end()) 
	{
		auto& callbacks = it->second;
		callbacks.erase(std::remove_if(callbacks.begin(), callbacks.end(),
			[&callback](const Callback& c) {
				return c.target_type() == callback.target_type();
			}), callbacks.end());

		if (callbacks.empty()) 
		{
			Subscribers.erase(it); // Remove the event if there are no more subscriptions
		}
	}
}

void EventSystemManager::Emit(EventID event) 
{
	auto it = Subscribers.find(event);
	if (it != Subscribers.end()) 
	{
		for (const auto& callback : it->second) 
		{
			callback();
		}
	}
}