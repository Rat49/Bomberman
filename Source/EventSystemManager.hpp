#ifndef EVENTSYSTEMMANAGER_HPP
#define EVENTSYSTEMMANAGER_HPP

#include <functional>
#include <map>
#include <vector>

enum class EventID {
	WindowClosed,

};

class EventSystemManager
{
public:
	static EventSystemManager& GetInstance();

	using Callback = std::function<void()>;

	void Subscribe(EventID event, Callback callback);

	void Unsubscribe(EventID event, Callback callback);

	void Emit(EventID event);

private:
	EventSystemManager() = default;
	std::map<EventID, std::vector<Callback>> Subscribers;
};

#endif // EVENTSYSTEMMANAGER_HPP