#include "PlaceBombs.hpp"

PlaceBombs::PlaceBombs(int32_t requiredBombs, int32_t eventId, int32_t eventFinished) : BaseObjective(requiredBombs, eventId, eventFinished) {}

void PlaceBombs::onEvent() {
	//std::cout << "-> Overriden event for bombs\n";
	if (currentCount < requiredCount) {
		currentCount++;
	}
	checkCompletion();
}