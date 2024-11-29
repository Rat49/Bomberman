#pragma once
#include <string>
#include "Common/Modules.hpp"
#include "TestBase.hpp"

class BoosterManagerTest : public TestBase
{
public:
	const std::string& getName() const override;
	void setup() override;
	void run() override;
	void update(float deltaTime, sf::RenderWindow* window) override;
	bool isComplete() const override;
private:
	std::string m_name = "BoostersManagerTest";
};

