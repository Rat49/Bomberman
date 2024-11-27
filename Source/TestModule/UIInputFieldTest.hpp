#pragma once

#include "TestModule/TestBase.hpp"
#include <string>
#include <memory>

class UIInputField;
class UILabel;
class UIScreen;

class UIInputFieldTest : public TestBase
{
public:

	const std::string& getName() const override;

	void setup() override;

	void run() override;

	void update(float deltaTime, sf::RenderWindow* window) override;

	bool isComplete() const override;

private:

	std::string m_name = "UI InputField test";

	std::shared_ptr<UIScreen> m_screen;

	std::shared_ptr<UIInputField> m_inputField;

	std::shared_ptr<UILabel> m_label;
	
	bool m_isCompleted = false;

};

