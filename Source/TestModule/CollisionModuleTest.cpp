#include "CollisionModuleTest.hpp"
#include "Common/Logs.hpp"
#include "Common/Modules.hpp"
#include "EventSystem/EventSystem.hpp"
#include <iostream>
#include <random>
#include <thread>
#include <chrono>

int32_t IDBeginOverlap;
int32_t IDEndOverlap;

float getRandomFloat(float min, float max) {
	static std::random_device rd;   
	static std::mt19937 gen(rd());  
	std::uniform_real_distribution<> dis(min, max);
	return float(dis(gen));
}

CollisionModuleTest::CollisionModuleTest() {
	rectangle.setPosition(sf::Vector2f(100.f, 100.f));
	rectangle.setSize(sf::Vector2f(100.f, 100.f));
}

CollisionModuleTest::CollisionModuleTest(const sf::Vector2f& position, const sf::Vector2f& size) {
	rectangle.setPosition(position);
	rectangle.setSize(size);
}

const std::string& CollisionModuleTest::getName() const
{
	return Name;
}

void CollisionModuleTest::setup() {
	IDBeginOverlap = Modules::Events->registerEvent();
	IDEndOverlap = Modules::Events->registerEvent();

	HandleBeginOverlap = Modules::Events->subscribe(IDBeginOverlap,
		std::bind(&CollisionModuleTest::BeginOverlapHandler, this, std::placeholders::_1));

	HandleEndOverlap = Modules::Events->subscribe(IDEndOverlap,
		std::bind(&CollisionModuleTest::EndOverlapHandler, this, std::placeholders::_1));
}

void CollisionModuleTest::run() {

}

void CollisionModuleTest::update(CollisionRectangle& other) {
	bool isCurrentlyOverlapping = isOverlapping(other);
	if (isCurrentlyOverlapping && !getIsOverlapped()) {
		setIsOverlapped(true);
		Modules::Events->emit(IDBeginOverlap, &other);  // Trigger BeginOverlap event
	}
	else if (!isCurrentlyOverlapping && getIsOverlapped()) {
		setIsOverlapped(false);
		Modules::Events->emit(IDEndOverlap, &other);    // Trigger EndOverlap event
	}
}

void CollisionModuleTest::update(float, sf::RenderWindow* window) {

	window->setSize(sf::Vector2u(800, 600));

	float minWidth = 50.f, maxWidth = 100.f;
	float minHeight = 20.f, maxHeight = 70.f;

	// Create two Collision rectangles with random sizes
	sf::Vector2f size1(getRandomFloat(minWidth, maxWidth), getRandomFloat(minHeight, maxHeight));
	sf::Vector2f size2(getRandomFloat(minWidth, maxWidth), getRandomFloat(minHeight, maxHeight));

	CollisionModuleTest rect1(sf::Vector2f(50.f, 50.f), size1);
	CollisionModuleTest rect2(sf::Vector2f(100.f, 100.f), size2);
	for (int i = 0; i < 20;i++) {
		size1 = { getRandomFloat(minWidth, maxWidth), getRandomFloat(minHeight, maxHeight) };
		size2 = { getRandomFloat(minWidth, maxWidth), getRandomFloat(minHeight, maxHeight) };

		rect1.getRectangle().setSize(size1);
		rect2.getRectangle().setSize(size2);

		rect1.update(rect2);
		if (rect1.getIsOverlapped()) {
			LOG("Collision");
		}
		else {
			LOG("No Collision");
		}

		window->clear();

		// Color the Rectangles
		rect1.setColor(sf::Color::Red);
		rect2.setColor(sf::Color::Blue);
		// Draw the rectangles
		window->draw(rect1.getRectangle());
		window->draw(rect2.getRectangle());

		window->display();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	window->setSize(sf::Vector2u(200, 200));
}

bool CollisionModuleTest::isComplete() const {
	Modules::Events->unsubscribe(IDBeginOverlap, HandleBeginOverlap);
	Modules::Events->unsubscribe(IDEndOverlap, HandleEndOverlap);

	return true;
}
void CollisionModuleTest::BeginOverlapHandler(void*) {
	LOG("Begin Overlap");
}

void CollisionModuleTest::EndOverlapHandler(void*) {
	LOG("End Overlap");
}