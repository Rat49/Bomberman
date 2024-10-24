#pragma once

#include "TestModule/TestBase.hpp"

class MockActor;
class CollisionModuleTest : public TestBase
{
public:
	const std::string& getName() const override;
	void setup() override;
	void run() override;
	void update(float, sf::RenderWindow* window) override;
	bool isComplete() const override;

private:
	const std::string Name = "CollisionModuleTest";
	MockActor* actor1;
	MockActor* actor2;
};