#include "EventSystem/EventSystem.hpp"

int32_t EventSystem::registerEvent() {
	return nextEventID++;
}

void EventSystem::unsubscribe(int32_t eventID, FunctionHandle handle) {
	auto it = subscribers.find(eventID);

	if (it != subscribers.end()) {
		auto& callbackList = it->second;

		// Remove a callback based on its handle
		callbackList.erase(
			std::remove_if(callbackList.begin(), callbackList.end(),
				[handle](const Subscriber& sub) {
					return sub.handle == handle;
				}),
			callbackList.end());

		// If there are no more callbacks, remove the event
		if (callbackList.empty()) {
			subscribers.erase(it);
		}
	}
}