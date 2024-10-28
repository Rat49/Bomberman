#include "CreateObjective.hpp"
#include "PlaceBombs.hpp"
#include "DestroyBlocks.hpp"
#include "Common/Modules.hpp"
#include "EventSystem/EventSystem.hpp"

std::unique_ptr<BaseObjective> CreateObjective::createObjective(int32_t value, int32_t requiredCnt, int32_t eventFinished)
{
	EventType myType = static_cast<EventType>(value);
	switch (value) {
	case 0:
		return std::make_unique<PlaceBombs>(requiredCnt, eventIds[myType], eventFinished);
		break;
	case 1:
		return std::make_unique<DestroyBlocks>(requiredCnt, eventIds[myType], eventFinished);
		break;
	default:
		return std::make_unique<DestroyBlocks>(requiredCnt, eventIds[myType], eventFinished);
		break;
	}
}

void CreateObjective::registerAllEvents()
{
	eventIds[EventType::PlaceBombs] = Modules::Events->registerEvent();
	eventIds[EventType::DestroyBlocks] = Modules::Events->registerEvent();
}

void CreateObjective::emitEvent(const EventType& name)
{
	Modules::Events->emit(eventIds[name], nullptr);
}
