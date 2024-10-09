#include "EventSystem.hpp"

EventSystem& EventSystem::getInstance()
{
	// create and return a static instance of EventSystem
	static EventSystem instance;
	return instance;
}

int32_t EventSystem::registerEvent()
{
	// return the current ID and increment it for the next event
	return nextEventID++;
}

void EventSystem::subscribe(int32_t eventID, Callback callback)
{
	// get the vector of callbacks for the specified event
	auto& callbacks = subscribers[eventID]; 

	// check if the callback is already subscribed
	auto it = std::find_if(callbacks.begin(), callbacks.end(),
		[&callback](const Callback& c) {
			return c.target_type() == callback.target_type();
		});

	// If the callback is not already subscribed
	if (it == callbacks.end()) 
	{
		// add the callback to the list
		callbacks.push_back(callback);
	}
}

void EventSystem::unsubscribe(int32_t eventID, Callback callback)
{
	// find the event in the subscribers map
	auto it = subscribers.find(eventID);

	// if the event exists
	if (it != subscribers.end()) 
	{
		// get the vector of callbacks for this event
		auto& callbacks = it->second;

		// remove the specified callback from the vector
		callbacks.erase(std::remove_if(callbacks.begin(), callbacks.end(),
			[&callback](const Callback& c) {
				return c.target_type() == callback.target_type();
			}), callbacks.end());

		// if there are no more callbacks for this event
		if (callbacks.empty()) 
		{
			// remove the event from the map
			subscribers.erase(it); 
	}
}

void EventSystem::emit(int32_t eventID)
{
	// find the event in the subscribers map
	auto it = subscribers.find(eventID);

	// if the event exists
	if (it != subscribers.end()) 
	{
		// call each callback associated with this event
		for (const auto& callback : it->second) 
		{
			// trigger the callback
			callback();
		}
	}
}
