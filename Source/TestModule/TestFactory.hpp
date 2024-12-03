#pragma once
#include "TestBase.hpp"
#include <memory>

class TestFactory
{
public:
	virtual std::pair<std::string, std::shared_ptr<TestBase>> createTest() const = 0;
};