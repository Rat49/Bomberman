#pragma once

#include "TestModule/TestBase.hpp"
#include "CollisionModule/CollisionRectangle.hpp"

class CollisionModuleTest : public TestBase, public CollisionRectangle
{
public:
	CollisionModuleTest();
	CollisionModuleTest(const sf::Vector2f& position, const sf::Vector2f& size);
	const std::string& getName() const override;
	void setup() override;
	void run() override;
	void update(float, sf::RenderWindow* window) override;
	bool isComplete() const override;

	//updates overlap status and emits events if needed
	void update(CollisionRectangle& other) override;

	//event handlers
	void BeginOverlapHandler(void* other) override;

	void EndOverlapHandler(void* other) override;
private:
	const std::string Name = "CollisionModuleTest";

	int32_t HandleBeginOverlap;
	int32_t HandleEndOverlap;
};