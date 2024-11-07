#include "TestAI.hpp"
#include "TestStates.hpp"
#include "TestTransitions.hpp"
#include "CollisionModule/PhysicsModule.hpp"
#include "Common/Logs.hpp"
#include "Common/Modules.hpp"
#include <thread>
#include <chrono>

const std::string& TestAI::getName() const {
	return Name;
}

void TestAI::setup() {
	actor1 = std::make_unique<MockActor>();
	actor2 = std::make_unique<MockActor>();

	auto idleState = std::make_shared<IdleState>();
	auto chaseState = std::make_shared<ChaseState>();

	// Set initial state
	(actor1->getAIController()).fsm->SetInitialState(idleState);

	// Add transitions (example)
	(actor1->getAIController()).fsm->AddTransition(idleState, std::make_shared<IdleToChaseTransition>(chaseState));
	(actor1->getAIController()).fsm->AddTransition(chaseState, std::make_shared<ChaseToIdleTransition>(idleState));
}

void TestAI::run() {
	
}

void TestAI::update(float, sf::RenderWindow* window) {

	void* parent = (actor1->getAIController()).getParent();
	MockActor* mockActorParent = static_cast<MockActor*>(parent);

	sf::Vector2f actor1Position(175.f, 175.f);
	std::vector<sf::Vector2f> actor2Positions = { {175.f, 30.f},
												{175.f, 320.f},
												{30.f, 175.f},
												{320.f, 175.f}
												};

	float distance = 200.f;
	std::vector<sf::Vector2f> directions = { {1,0}, //right
											{-1,0}, //left
											{0,1}, //down
											{0,-1} //up
	};
	// Create two Collision rectangles with random sizes
	sf::Vector2f size(50, 50);

	int direction = 0;
	int actor2Position = 0;
	sf::Vector2f endPoint; 
	
	actor1->getCollisionBox().setRectangleProperties(actor1Position, size);
	if (mockActorParent) {
		auto& box = mockActorParent->getCollisionBox();
		for (int i = 0; i < 20; i++) {
			actor2->getCollisionBox().setRectangleProperties(actor2Positions[actor2Position], size);
			if(i%3==0)
				actor2Position = (actor2Position + 1) % actor2Positions.size();

			bool isInRange = Modules::Physics->rayCast(box.getCenter(), directions[direction], distance, endPoint) != nullptr;
			actor1->getAIController().setIsPlayerInRange(isInRange);
			direction = (direction + 1) % directions.size();

			window->clear();

			// Color the Rectangles
			actor1->getCollisionBox().setColor(sf::Color::Red);
			actor2->getCollisionBox().setColor(sf::Color::Blue);
			// Draw the rectangles
			window->draw(actor1->getCollisionBox().getRectangle());
			window->draw(actor2->getCollisionBox().getRectangle());

			//color and draw a ray
			sf::VertexArray rayLine(sf::Lines, 2);
			rayLine[0].position = box.getCenter();
			rayLine[0].color = sf::Color::Green;
			rayLine[1].position = endPoint;
			rayLine[1].color = sf::Color::Green;

			window->draw(rayLine);

			window->display();
			actor1->getAIController().Update();
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
	}
}