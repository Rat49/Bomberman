#pragma once

#include "TestModule/TestBase.hpp"

class CollisionModuleTest : public TestBase
{
public:
	const std::string& getName() const override;
	void setup() override;
	void run() override;
	void update(float ) override { }
	bool isComplete() const override { return true; };

private:
	const std::string Name = "CollisionModuleTest";
	int32_t IDBeginOverlap;
	int32_t IDEndOverlap;
};