#include "CollisionModuleTest.hpp"
#include "CollisionModule/MockActor.hpp"
#include "Common/Logs.hpp"
#include "Common/Modules.hpp"
#include <iostream>
#include <random>
#include <thread>
#include <chrono>

float getRandomFloat(float min, float max) {
	static std::random_device rd;   
	static std::mt19937 gen(rd());  
	std::uniform_real_distribution<> dis(min, max);
	return float(dis(gen));
}

const std::string& CollisionModuleTest::getName() const
{
	return Name;
}

void CollisionModuleTest::setup() {
	actor1 = new MockActor();
	actor2 = new MockActor();
}

void CollisionModuleTest::run() {

}

void CollisionModuleTest::update(float, sf::RenderWindow* window) {

	window->setSize(sf::Vector2u(800, 600));

	float minWidth = 50.f, maxWidth = 100.f;
	float minHeight = 20.f, maxHeight = 70.f;

	sf::Vector2f position1(50.f, 50.f);
	sf::Vector2f position2(100.f, 100.f);
	// Create two Collision rectangles with random sizes
	sf::Vector2f size1;
	sf::Vector2f size2;

	for (int i = 0; i < 20;i++) {
		size1 = { getRandomFloat(minWidth, maxWidth), getRandomFloat(minHeight, maxHeight) };
		size2 = { getRandomFloat(minWidth, maxWidth), getRandomFloat(minHeight, maxHeight) };

		actor1->collisionBox->setRectangleProperties(position1, size1);
		actor2->collisionBox->setRectangleProperties(position2, size2);

		actor1->collisionBox->update(*actor2->collisionBox);
		if (actor1->collisionBox->getIsOverlapped()) {
			LOG("Collision");
		}
		else {
			LOG("No Collision");
		}

		window->clear();

		// Color the Rectangles
		actor1->collisionBox->setColor(sf::Color::Red);
		actor2->collisionBox->setColor(sf::Color::Blue);
		// Draw the rectangles
		window->draw(actor1->collisionBox->getRectangle());
		window->draw(actor2->collisionBox->getRectangle());

		window->display();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	window->setSize(sf::Vector2u(200, 200));

	//test for parent pointer
	void* parent = actor1->collisionBox->getParent();
	MockActor* mockActorParent = static_cast<MockActor*>(parent);
	mockActorParent->print();
}

bool CollisionModuleTest::isComplete() const {
	delete actor1;
	delete actor2;

	return true;
}