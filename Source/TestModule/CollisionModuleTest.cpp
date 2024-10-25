#include "CollisionModuleTest.hpp"
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

const std::string& CollisionModuleTest::getName() const {
	return Name;
}

void CollisionModuleTest::setup() {
	actor1 = std::make_unique<MockActor>();
	actor2 = std::make_unique<MockActor>();
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

	for (int i = 0; i < 20; i++) {
		size1 = { getRandomFloat(minWidth, maxWidth), getRandomFloat(minHeight, maxHeight) };
		size2 = { getRandomFloat(minWidth, maxWidth), getRandomFloat(minHeight, maxHeight) };

		actor1->getCollisionBox().setRectangleProperties(position1, size1);
		actor2->getCollisionBox().setRectangleProperties(position2, size2);

		actor1->getCollisionBox().update(actor2->getCollisionBox());
		if (actor1->getCollisionBox().getIsOverlapped()) {
			LOG("Collision");
		}
		else {
			LOG("No Collision");
		}

		window->clear();

		// Color the Rectangles
		actor1->getCollisionBox().setColor(sf::Color::Red);
		actor2->getCollisionBox().setColor(sf::Color::Blue);
		// Draw the rectangles
		window->draw(actor1->getCollisionBox().getRectangle());
		window->draw(actor2->getCollisionBox().getRectangle());

		window->display();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	window->setSize(sf::Vector2u(200, 200));

	//test for parent pointer
	void* parent = actor1->getCollisionBox().getParent();
	MockActor* mockActorParent = static_cast<MockActor*>(parent);
	mockActorParent->print();
}
