#pragma once
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

class BaseObjective;

enum class EventType {
	PlaceBombs,
	DestroyBlocks
};

class CreateObjective {
public:
	static CreateObjective& getInstance() {
		static CreateObjective instance;
		return instance;
	}

	std::unique_ptr<BaseObjective> createObjective(int32_t value, int32_t requiredCnt, int32_t eventFinished);

	void registerAllEvents();

	void emitEvent(const EventType& name);

private:
	std::unordered_map<EventType, int32_t> eventIds;
};