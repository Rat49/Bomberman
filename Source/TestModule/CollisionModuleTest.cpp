#include "CollisionModuleTest.hpp"
#include "CollisionModule/PhysicsModule.hpp"
#include "Common/Logs.hpp"
#include "Common/Modules.hpp"
#include <chrono>
#include <iostream>
#include <random>
#include <thread>

float getRandomFloat(float min, float max)
{
    static std::random_device        rd;
    static std::mt19937              gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return float(dis(gen));
}

const std::string& CollisionModuleTest::getName() const
{
    return Name;
}

void CollisionModuleTest::setup()
{
    actor1 = std::make_unique<MockActor>();
    actor2 = std::make_unique<MockActor>();
}

void CollisionModuleTest::run()
{
}

void CollisionModuleTest::update(float, sf::RenderWindow* window)
{

    float minWidth = 50.f, maxWidth = 100.f;
    float minHeight = 20.f, maxHeight = 70.f;

    sf::Vector2f position1(50.f, 50.f);
    sf::Vector2f position2(50.f, 135.f);

    //ray origin,distance and directions
    sf::Vector2f              origin(120.f, 120.f);
    float                     distance   = 200.f;
    std::vector<sf::Vector2f> directions = {
        {1, 0},  //right
        {-1, 0}, //left
        {0, 1},  //down
        {0, -1}  //up
    };
    // Create two Collision rectangles with random sizes
    sf::Vector2f size1;
    sf::Vector2f size2;

    int          direction = 0;
    sf::Vector2f endPoint;
    //bool isIntersecting;
    for (int i = 0; i < 20; i++)
    {
        size1 = {getRandomFloat(minWidth, maxWidth), getRandomFloat(minHeight, maxHeight)};
        size2 = {getRandomFloat(minWidth, maxWidth), getRandomFloat(minHeight, maxHeight)};

        actor1->getCollisionBox().setRectangleProperties(position1, size1);
        actor2->getCollisionBox().setRectangleProperties(position2, size2);

        /* for box collision test
		actor1->getCollisionBox().update(actor2->getCollisionBox());
		if (actor1->getCollisionBox().getIsOverlapped()) {
			LOG("Collision");
		}
		else {
			LOG("No Collision");
		}
		*/
        const CollisionComponent* intersected = Modules::Physics->rayCast(origin, directions[direction], distance, endPoint);
        if (intersected)
        {
            LOG("Collision");
        }
        else
        {
            LOG("No Collision");
            endPoint = {origin + directions[direction] * distance};
        }

        //setting direction in circular pattern
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
        rayLine[0].position = origin;
        rayLine[0].color    = sf::Color::Green;
        rayLine[1].position = endPoint;
        rayLine[1].color    = sf::Color::Green;

        window->draw(rayLine);

        window->display();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    //test for parent pointer
    void*      parent          = actor1->getCollisionBox().getParent();
    MockActor* mockActorParent = static_cast<MockActor*>(parent);
    mockActorParent->print();
}
