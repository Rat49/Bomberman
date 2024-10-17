#include "CollisionModuleTest.hpp"
#include "CollisionModule/CollisionRectangle.hpp"
#include "Common/Logs.hpp"
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
}

void CollisionModuleTest::run() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "CollisionModule Test");

	float minWidth = 50.f, maxWidth = 200.f;
	float minHeight = 50.f, maxHeight = 150.f;

	while (window.isOpen()) {
		sf::Vector2f size1(getRandomFloat(minWidth, maxWidth), getRandomFloat(minHeight, maxHeight));
		sf::Vector2f size2(getRandomFloat(minWidth, maxWidth), getRandomFloat(minHeight, maxHeight));

		// Create two Collision rectangles with random sizes
		CollisionRectangle rect1(sf::Vector2f(100.f, 100.f), size1);
		CollisionRectangle rect2(sf::Vector2f(220.f, 160.f), size2);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Check for overlap between the two rectangles
		if (rect1.isOverlapping(rect2)) {
			LOG("Collision");
		}
		else {
			LOG("No Collision");
		}

		window.clear();

		// Color the Rectangles
		rect1.setColor(sf::Color::Red);
		rect2.setColor(sf::Color::Blue);
		// Draw the rectangles
		window.draw(rect1.getRectangle());
		window.draw(rect2.getRectangle());

		window.display();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}