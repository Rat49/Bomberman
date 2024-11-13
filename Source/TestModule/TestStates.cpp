#include "TestStates.hpp"

void IdleState::Enter(AIController* ){
	std::cout << "Entering Idle State\n";
}

void IdleState::Update(AIController* ){
	std::cout << "AI is idle.\n";
}

void IdleState::Exit(AIController* ){
	std::cout << "Exiting Idle State\n";
}

void ChaseState::Enter(AIController* ) {
	std::cout << "Entering Chase State\n";
}

void ChaseState::Update(AIController* ) {
	std::cout << "AI is chasing the player.\n";
}

void ChaseState::Exit(AIController* ) {
	std::cout << "Exiting Chase State\n";
}