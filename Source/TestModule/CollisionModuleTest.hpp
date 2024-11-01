#pragma once

#include "TestModule/TestBase.hpp"
#include "MockActor.hpp"
#include <memory>

class CollisionModuleTest : public TestBase
{
public:
	const std::string& getName() const override;
	void setup() override;
	void run() override;
	void update(float, sf::RenderWindow* window) override;
	bool isComplete() const override { return true; };

private:
	const std::string Name = "CollisionModuleTest";
	std::unique_ptr<MockActor> actor1;
	std::unique_ptr<MockActor> actor2;

};