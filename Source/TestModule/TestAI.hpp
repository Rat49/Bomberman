#pragma once

#include "TestModule/TestBase.hpp"
#include "MockActor.hpp"
#include <memory>

class TestAI : public TestBase
{
public:
	const std::string& getName() const override;
	void setup() override;
	void run() override;
	void update(float, sf::RenderWindow* window) override;
	bool isComplete() const override { return true; };

private:
	const std::string Name = "TestAI";
	std::unique_ptr<MockActor> actor1;
	std::unique_ptr<MockActor> actor2;

};